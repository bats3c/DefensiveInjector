#define dwAllowDllCount 4
CHAR cAllowDlls[dwAllowDllCount][MAX_PATH] = {
                                                "W:\\allowed.dll",
                                                "C:\\Windows\\system32\\rsaenh.dll",
                                                "C:\\Windows\\system32\\bcryptprimitives.dll",
                                                "ext-ms-win-kernel32-errorhandling-l1-1-0.dll"
                                             };

VOID HookLoadDll(LPVOID lpAddr);
NTSTATUS __stdcall _LdrLoadDll(PWSTR SearchPath OPTIONAL, PULONG DllCharacteristics OPTIONAL, PUNICODE_STRING DllName, PVOID *BaseAddress);

typedef void (WINAPI * LdrLoadDll_) (PWSTR SearchPath OPTIONAL,
                                     PULONG DllCharacteristics OPTIONAL,
                                     PUNICODE_STRING DllName,
                                     PVOID *BaseAddress);

LPVOID lpAddr;
CHAR OriginalBytes[13] = {};

 typedef struct _INITIAL_TEB
 {
     PVOID PreviousStackBase;
     PVOID PreviousStackLimit;
     PVOID StackBase;
     PVOID StackLimit;
     PVOID AllocatedStackBase;
 } INITIAL_TEB, *PINITIAL_TEB;

typedef BOOL (WINAPI * CryptDestroyKey_)      (HCRYPTKEY hKey);
typedef BOOL (WINAPI * CryptDestroyHash_)     (HCRYPTHASH hHash);
typedef BOOL (WINAPI * CryptReleaseContext_)  (HCRYPTPROV hProv, DWORD dwFlags);
typedef BOOL (WINAPI * CryptHashData_)        (HCRYPTHASH hHash, const BYTE *pbData, DWORD dwDataLen, DWORD dwFlags);
typedef BOOL (WINAPI * CryptCreateHash_)      (HCRYPTPROV hProv, ALG_ID Algid, HCRYPTKEY hKey, DWORD dwFlags, HCRYPTHASH *phHash);
typedef BOOL (WINAPI * CryptDeriveKey_)       (HCRYPTPROV hProv, ALG_ID Algid, HCRYPTHASH hBaseData, DWORD dwFlags, HCRYPTKEY *phKey);
typedef BOOL (WINAPI * CryptDecrypt_)         (HCRYPTKEY hKey, HCRYPTHASH hHash, BOOL Final, DWORD dwFlags, BYTE *pbData, DWORD *pdwDataLen);
typedef BOOL (WINAPI * CryptAcquireContextW_) (HCRYPTPROV *phProv, LPCWSTR szContainer, LPCWSTR szProvider, DWORD dwProvType, DWORD dwFlags);

CryptDecrypt_         fnCryptDecrypt;
CryptHashData_        fnCryptHashData;
CryptDeriveKey_       fnCryptDeriveKey;
CryptDestroyKey_      fnCryptDestroyKey;
CryptCreateHash_      fnCryptCreateHash;
CryptDestroyHash_     fnCryptDestroyHash;
CryptReleaseContext_  fnCryptReleaseContext;
CryptAcquireContextW_ fnCryptAcquireContextW;