#ifndef __LIBRARY_H
#define __LIBRARY_H

#include "Module.h"
#include "Portability.h"

namespace WPEFramework {
namespace Core {
    class EXTERNAL Library {
    private:
        typedef struct {
            uint32_t _referenceCount;
#ifdef __LINUX__
            void* _handle;
#endif
#ifdef __WINDOWS__
            HMODULE _handle;
#endif
            string _name;

        } RefCountedHandle;

        typedef void (*ModuleUnload)();

    public:
        Library();
        Library(const TCHAR fileName[]);
        Library(const Library& copy);
        ~Library();

        Library& operator=(const Library& RHS);

    public:
        inline bool IsLoaded() const
        {
            return (_refCountedHandle != nullptr);
        }
        inline const string& Error() const
        {
            return (_error);
        }
        inline const string& Name() const
        {
            static const string emptyString;

            return (_refCountedHandle != nullptr ? _refCountedHandle->_name : emptyString);
        }
        void* LoadFunction(const TCHAR functionName[]);

    private:
        void AddRef();
        uint32_t Release();

    private:
        RefCountedHandle* _refCountedHandle;
        string _error;
    };
}
} // namespace Core

#endif
