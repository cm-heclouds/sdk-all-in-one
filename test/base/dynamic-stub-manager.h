#ifndef DYNAMIC_STUB_MANAGER_H_
#define DYNAMIC_STUB_MANAGER_H_

#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <map>
#include <string>
#include <exception>

class DynamicStubManager {
  public:
    template<class T>
    void MakeStub(T original, T stub)
    {
        char *src_addr = reinterpret_cast<char*>(original);
        InstructionHole &hole = stubs_[src_addr];

        memcpy(&hole.ins, src_addr, sizeof(hole));

        const size_t page_size = sysconf(_SC_PAGESIZE);
        char *aligned_addr = src_addr - reinterpret_cast<size_t>(src_addr) % page_size;

        if (mprotect(aligned_addr, page_size,
                     PROT_READ | PROT_WRITE | PROT_EXEC) == -1) {
            stubs_.erase(src_addr);
            std::string msg = "Failed to modify the protection of the memory: ";
            msg += strerror(errno);
            throw msg;
        }

        src_addr[0] = (uint8_t)0x48;
        src_addr[1] = (uint8_t)0xb8;

        char *stub_addr = reinterpret_cast<char*>(stub);
        memcpy(src_addr + 2, &stub_addr, sizeof(stub));

        src_addr += 2 + sizeof(&stub);
        src_addr[0] = (uint8_t)0xff;
        src_addr[1] = (uint8_t)0xe0;
    }

    template<class T>
    void UnmakeStub(T original)
    {
        void *addr = reinterpret_cast<void*>(original);
        Stubs::iterator i = stubs_.find(addr);
        if (stubs_.end() != i) {
            memcpy(addr, i->second.ins, sizeof(InstructionHole));
            stubs_.erase(i);
        }
    }
  private:
    struct InstructionHole {
        char ins[16];
    };

    typedef std::map<void*, InstructionHole> Stubs;

    Stubs stubs_;
};

#endif /* DYNAMIC_STUB_MANAGER_H_ */
