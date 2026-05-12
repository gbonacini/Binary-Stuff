// -----------------------------------------------------------------
// Copyright (C) 2025  Gabriele Bonacini
//
// MinIO a cstdlib like self-consistent library written using c++ 
// and inline asm
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
// -----------------------------------------------------------------

#pragma once

namespace minIO {

#if defined(__x86_64__)

using int64_t=long long;
using uchar=unsigned char;
using uint64_t=unsigned long long;
using uint32_t=unsigned int;
using uint16_t=unsigned short;
using size_t=unsigned long long;
using ssize_t=long long;
using loff_t=long long;
using socklen_t=unsigned int;

using mode_t=unsigned int;

const mode_t S_EMPTY      {00000000},  
             S_IRWXU      {00000700},  
             S_IRUSR      {00000400},  
             S_IWUSR      {00000200},  
             S_IXUSR      {00000100},  
             S_IRWXG      {00000070},  
             S_IRGRP      {00000040},  
             S_IWGRP      {00000020},  
             S_IXGRP      {00000010},  
             S_IRWXO      {00000007},  
             S_IROTH      {00000004},  
             S_IWOTH      {00000002},  
             S_IXOTH      {00000001},  
             S_ISUID      {00004000},  
             S_ISGID      {00002000},  
             S_ISVTX      {00001000},  
             O_ACCMODE    {00000003},
             O_RDONLY     {00000000},
             O_WRONLY     {00000001},
             O_RDWR       {00000002},
             O_CREAT      {00000100},   
             O_EXCL       {00000200}, 
             O_NOCTTY     {00000400}, 
             O_TRUNC      {00001000}, 
             O_APPEND     {00002000},
             O_NONBLOCK   {00004000},
             O_DSYNC      {00010000}, 
             FASYNC       {00020000}, 
             O_DIRECT     {00040000}, 
             O_LARGEFILE  {00100000},
             O_DIRECTORY  {00200000}, 
             O_NOFOLLOW   {00400000}, 
             O_NOATIME    {01000000},
             O_CLOEXEC    {02000000}; 


ssize_t write(int fd, const char* txt, size_t len) noexcept {

    ssize_t ret { -1 };
    if(fd < 0 || len == 0 || txt == nullptr) return ret;

    asm volatile (
        "\nmov %1, %%rax"
        "\nmov %2, %%rdi"
        "\nmov %3, %%rsi"
        "\nmov %4, %%rdx"
        "\nsyscall"
        "\nmov %%rax, %0"
        : "=r" (ret)
        : "i"  (1ULL),
          "r"  (static_cast<uint64_t>(fd)),
          "r"  (txt),
          "r"  (static_cast<uint64_t>(len))
        : "%rax", "%rdi", "%rsi", "%rdx", "%rcx", "%r11", "memory");

    return ret;
}

int64_t printScreen(const char* txt, uint64_t len) noexcept {
    return write(1, txt, len);
}

ssize_t read(int fd, char* txt, size_t len) noexcept {

    ssize_t ret { -1 };
    if(fd < 0 || len == 0 || txt == nullptr) return ret;

    asm volatile (
        "\nmov %1, %%rax"
        "\nmov %2, %%rdi"
        "\nmov %3, %%rsi"
        "\nmov %4, %%rdx"
        "\nsyscall"
        "\nmov %%rax, %0"
        : "=r" (ret)
        : "i"  (0ULL),
          "r"  (static_cast<uint64_t>(fd)),
          "r"  (txt),
          "r"  (len)
        : "%rax", "%rdi", "%rsi", "%rdx", "%rcx", "%r11", "memory");

    return ret;
}

ssize_t copy_n(const uchar* in, size_t len, uchar* out){
     ssize_t ret { -1 };
     if(in == nullptr || out ==nullptr || len == 0)
          return ret;

     for(size_t idx{0}; idx<len; idx++){
         out[idx] = in[idx];
     }

     return len;
}

char getChar(void){
   char buff {0};
   auto ret { read(0, &buff, 1) };

   return ret != -1 ? buff : 0;
}

void exit(bool err=false) noexcept {

    uint64_t ret { err ? 1ULL : 0ULL };
    asm volatile (
        "\nmov %0, %%rax"
        "\nmov %1, %%rdi"
        "\nsyscall"
        : // void
        : "i"  (0x3cULL),
          "r"  (ret)
        : "%rax", "%rdi", "%rcx", "%r11");
}

int64_t open(const char *path, mode_t flags, mode_t mode=S_EMPTY)  noexcept {

    int64_t ret { -1 };
    if(path == nullptr) return ret;

    asm volatile (
        "\nmov %1, %%rax"
        "\nmov %2, %%rdi"
        "\nmov %3, %%rsi"
        "\nmov %4, %%rdx"
        "\nsyscall"
        "\nmov %%rax, %0"
        : "=r" (ret)
        : "i"  (0x02ULL),
          "r"  (path),
          "r"  (static_cast<uint64_t>(flags)),
          "r"  (static_cast<uint64_t>(mode))
        : "%rax", "%rdi", "%rsi", "%rdx", "%rcx", "%r11", "memory");

    return ret;
}

int64_t close(int fd)  noexcept {

    int64_t ret { -1 };
    if(fd < 0) return ret;

    asm volatile (
        "\nmov %1, %%rax"
        "\nmov %2, %%rdi"
        "\nsyscall"
        "\nmov %%rax, %0"
        : "=r" (ret)
        : "i"  (0x03ULL),
          "r"  (static_cast<uint64_t>(fd))
        : "%rax", "%rdi", "%rcx", "%r11");

    return ret;
}

int64_t rename(const char *old, const char *neww)  noexcept {

    int64_t ret { -1 };
    if(old == nullptr || neww == nullptr ) return ret;

    asm volatile (
        "\nmov %1, %%rax"
        "\nmov %2, %%rdi"
        "\nmov %3, %%rsi"
        "\nsyscall"
        "\nmov %%rax, %0"
        : "=r" (ret)
        : "i"  (0x52ULL),
          "r"  (old),
          "r"  (neww)
        : "%rax", "%rdi", "%rsi", "%rcx", "%r11", "memory");

    return ret;
}

int64_t unlink(const char *todelete)  noexcept {

    int64_t ret { -1 };
    if(todelete == nullptr ) return ret;

    asm volatile (
        "\nmov %1, %%rax"
        "\nmov %2, %%rdi"
        "\nsyscall"
        "\nmov %%rax, %0"
        : "=r" (ret)
        : "i"  (0x57ULL),
          "r"  (todelete)
        : "%rax", "%rdi", "%rcx", "%r11", "memory");

    return ret;
}

size_t strnlen(const char* txt, uint64_t maxDigits) noexcept {

    if(maxDigits == 0 || txt == nullptr) return 0;

    size_t len { 0 };
    for( ; txt[len] != 0 && len < maxDigits; len++);

    return len <= maxDigits ? len : 0;
}

const char* digitToTxt(uchar digit) noexcept {
    static const char lookup[11] { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ' };
    return &lookup[digit < 10 ? digit : 10];
}

char digitToChar(uchar digit) noexcept {
    return *digitToTxt(digit);
}

void printDigit(uchar digit) noexcept {
    printScreen(digitToTxt(digit), 1);
}

void printNumber(uint64_t number) noexcept {
    const  uint32_t    MAX_DIGITS         { 20 };
    static uchar       numTxt[MAX_DIGITS];
    
    if(number != 0){
       int idx{0};
       for(; idx < MAX_DIGITS; idx++) numTxt[idx] = 0;

       idx=MAX_DIGITS-1;
       for(; number > 0; number /= 10){
           uchar digit         { static_cast<uchar>(number % 10) };
           numTxt[idx]         = digit;
           idx--;
       }

       idx++;
       for(; idx < MAX_DIGITS; idx++)
           printDigit(numTxt[idx]);

    } else {

       printDigit(0);

    }
}

const char* numberToString(uint64_t number) noexcept {
    const uint32_t    MAX_DIGITS         { 20 };
    static char       numTxt[MAX_DIGITS + 1];
    
    int idx{0};
    if(number != 0){
       for(; idx <= MAX_DIGITS; idx++) numTxt[idx] = 0;

       idx=MAX_DIGITS-1;
       for(; number > 0; number /= 10){
           uchar digit         { static_cast<uchar>(number % 10) };
           numTxt[idx]         = digitToChar(digit);
           idx--;
       }

       idx++;

    } else {
       idx = MAX_DIGITS - 1;
       numTxt[idx] = '0';
    }

    return numTxt + idx;
}

struct sockaddr {
  short          sin_family;   // AF_INET
  uint16_t       sin_port;     // Port in network byte order
  uint32_t       sin_addr;     // IPv4 address in network byte order
  uchar          sin_zero[8];  // Padding to match struct sockaddr
};

using Sockaddr=struct sockaddr;

enum FLAGS : uint32_t {
      MSG_MORE		= 0x8000
};

enum SOCK_TYPE : uint32_t {
        // For now, only limited support
	SOCK_STREAM	   = 1,
	SOCK_DGRAM	   = 2,
    SOCK_SEQPACKET = 5
        /* 
	SOCK_RAW	= 3,
	SOCK_RDM	= 4,
	SOCK_SEQPACKET	= 5,
	SOCK_DCCP	= 6,
	SOCK_PACKET	= 10
        */
};

enum PROTOCOL_TYPE : uint32_t {
  // For now, only limited support
  DEFAULT=0,          // Dummy protocol for TCP
  IPPROTO_IP=0,       // Dummy protocol for TCP
  // IPPROTO_ICMP=1,  // Internet Control Message Protocol
  IPPROTO_TCP=6,      // Transmission Control Protocol
  IPPROTO_UDP=17      // User Datagram Protocol
};

enum FAMILY_TYPE : uint32_t {
    // For now, only limited support
    AF_INET= 2,
    AF_ALG = 38
};

enum SOCK_LEVELS : uint32_t{
    SOL_ALG=279
};

enum SOCK_ALGORITMS : uint32_t {
    ALG_SET_KEY=1,
    ALG_SET_IV=2,
    ALG_SET_OP=3,
    ALG_SET_AEAD_ASSOCLEN=4,
    ALG_SET_AEAD_AUTHSIZE=5
};

int socket(SOCK_TYPE type, PROTOCOL_TYPE protocol)  noexcept {

    int ret { -1 };

    asm volatile (
        "\nmov %1, %%rax"
        "\nmov %2, %%edi"
        "\nmov %3, %%esi"
        "\nmov %4, %%edx"
        "\nsyscall"
        "\nmov %%eax, %0"
        : "=r" (ret)
        : "i"  (0x29ULL),
          "i"  (FAMILY_TYPE::AF_INET),
          "r"  (type),
          "r"  (protocol)
        : "%rax", "%rdi", "%rsi", "%rdx", "%rcx", "%r11");

    return ret;
}

int socket(FAMILY_TYPE ft, SOCK_TYPE type, PROTOCOL_TYPE protocol)  noexcept {

    int ret { -1 };

    asm volatile (
        "\nmov %1, %%rax"
        "\nmov %2, %%rdi"
        "\nmov %3, %%rsi"
        "\nmov %4, %%rdx"
        "\nsyscall"
        "\nmov %%eax, %0"
        : "=r" (ret)
        : "i"  (0x29ULL),
          "r"  (static_cast<uint64_t>(ft)),
          "r"  (static_cast<uint64_t>(type)),
          "r"  (static_cast<uint64_t>(protocol))
        : "%rax", "%rdi", "%rsi", "%rdx", "%rcx", "%r11");

    return ret;
}

int64_t connect(int sockfd, const Sockaddr* addr, uint64_t addrlen) noexcept {

    int64_t ret { -1 };
    if(sockfd < 0 || addr == nullptr || addrlen == 0) return ret;

    asm volatile (
        "\nmov %1, %%rax"
        "\nmov %2, %%edi"
        "\nmov %3, %%rsi"
        "\nmov %4, %%rdx"
        "\nsyscall"
        "\nmov %%rax, %0"
        : "=r" (ret)
        : "i"  (0x2aULL),
          "r"  (sockfd),
          "r"  (addr),
          "r"  (addrlen)
        : "%rax", "%rdi", "%rsi", "%rdx", "%rcx", "%r11", "memory");

    return ret;
}

int64_t bind(int sockfd, const Sockaddr* addr, socklen_t addrlen){

    int64_t ret { -1 };
    if(sockfd < 0 || addr ==nullptr || addrlen == 0) return ret;

    asm volatile (
        "\nmov %1, %%rax"
        "\nmov %2, %%rdi"
        "\nmov %3, %%rsi"
        "\nmov %4, %%rdx"
        "\nsyscall"
        "\nmov %%rax, %0"
        : "=r" (ret)
        : "i"  (0x31ULL),
          "r"  (static_cast<uint64_t>(sockfd)),
          "r"  (addr),
          "r"  (static_cast<uint64_t>(addrlen))
        : "%rax", "%rdi", "%rsi", "%rdx", "%rcx", "%r11", "memory");

    return ret;
}

int64_t setsockopt(int sockfd, uint32_t level, int optname, const void *optval, socklen_t optlen){

    int64_t ret { -1 };
    if(sockfd < 0 || level < 0 || optname < 0 || optlen == 0) return ret;

    asm volatile (
        "\nmov %1, %%rax"
        "\nmov %2, %%rdi"
        "\nmov %3, %%rsi"
        "\nmov %4, %%rdx"
        "\nmov %5, %%r10"
        "\nmov %6, %%r8"
        "\nsyscall"
        "\nmov %%rax, %0"
        : "=r" (ret)
        : "i"  (0x36ULL),
          "r"  (static_cast<uint64_t>(sockfd)),
          "r"  (static_cast<uint64_t>(level)),
          "r"  (static_cast<uint64_t>(optname)),
          "r"  (optval),
          "r"  (static_cast<uint64_t>(optlen))
        : "%rax", "%rdi", "%rsi", "%rdx", "%r10", "%r8", "%rcx", "%r11", "memory");

    return ret;
}

int64_t accept(int sockfd, struct sockaddr* addr , socklen_t* len) noexcept {

    int64_t ret { -1 };
    if(sockfd < 0 ) return ret;

    asm volatile (
        "\nmov %1, %%rax"
        "\nmov %2, %%rdi"
        "\nmov %3, %%rsi"
        "\nmov %4, %%rdx"
        "\nsyscall"
        "\nmov %%rax, %0"
        : "=r" (ret)
        : "i"  (0x2BULL),
          "r"  (static_cast<uint64_t>(sockfd)),
          "r"  (addr),
          "r"  (len)
        : "%rax", "%rdi", "%rsi", "%rdx", "%rcx", "%r11", "memory");

    return ret;
}

int execve(const char *pathname, char *const argv[], char *const envp[]){

    int ret { -1 };
    if(pathname == nullptr || argv == nullptr) return ret;

    asm volatile (
        "\nmov %0, %%rax"
        "\nmov %1, %%rdi"
        "\nmov %2, %%rsi"
        "\nmov %3, %%rdx"
        "\nsyscall"
        : // void
        : "i"  (0x3BULL),
          "r"  (pathname),
          "r"  (argv),
          "r"  (envp)
        : "%rax", "%rdi", "%rsi", "%rdx", "memory");

    return ret;
}

ssize_t splice(int fd_in, loff_t *off_in, int fd_out, loff_t *off_out, size_t len, unsigned int flags){

    ssize_t ret { -1 };
    if(fd_in < 0 || fd_out < 0 ) return ret;

    asm volatile (
        "\nmov %1, %%rax"
        "\nmov %2, %%rdi"
        "\nmov %3, %%rsi"
        "\nmov %4, %%rdx"
        "\nmov %5, %%r10"
        "\nmov %6, %%r8"
        "\nmov %7, %%r9"
        "\nsyscall"
        "\nmov %%rax, %0"
        : "=r" (ret)
        : "i"  (0x113ULL),
          "g"  (static_cast<uint64_t>(fd_in)),
          "g"  (off_in),
          "g"  (static_cast<uint64_t>(fd_out)),
          "g"  (off_out),
          "g"  (len),
          "g"  (static_cast<uint64_t>(flags))
        : "%rax", "%rdi", "%rsi", "%rdx", "%r10", "%r8", "%r9", "%rcx", "%r11", "memory");

    return ret;
}

struct af_alg_iv {
	uint32_t	    ivlen;
	unsigned char	iv[0];
};

struct sockaddr_alg {
	uint16_t	    salg_family;
	unsigned char	salg_type[14];
	uint32_t	    salg_feat;
	uint32_t	    salg_mask;
	unsigned char	salg_name[64];
};

struct iovec {
    void*        iov_base;        // Starting address 
    size_t       iov_len;         // Size of the memory pointed to by iov_base. 
};

 struct msghdr {
    void*         msg_name;       // Optional address 
    socklen_t     msg_namelen;    // Size of address 
    struct iovec* msg_iov;        // Scatter/gather array 
    size_t        msg_iovlen;     // # elements in msg_iov 
    void*         msg_control;    // Ancillary data, see below 
    size_t        msg_controllen; // Ancillary data buffer len 
    int           msg_flags;      // Flags (unused) 
 };

/* Structure used for storage of ancillary data object information.  */
struct cmsghdr {
    size_t cmsg_len;		      // Length of data in cmsg_data plus length
				                  // of cmsghdr structure.
				                  // !! The type should be socklen_t but the
				                  // definition of the kernel is incompatible
				                  // with this. 

    int cmsg_level;		          // Originating protocol.
    int cmsg_type;		          // Protocol specific type.
};

#define CMSG_FIRSTHDR(mhdr) ((size_t) (mhdr)->msg_controllen >= sizeof(struct minIO::cmsghdr)	\
   ? reinterpret_cast<struct minIO::cmsghdr *>((mhdr)->msg_control) : nullptr)

#define CMSG_ALIGN(len) (((len) + sizeof(size_t) - 1) & (size_t) ~(sizeof(size_t) - 1))

#define CMSG_SPACE(len) (CMSG_ALIGN (len) + CMSG_ALIGN (sizeof(struct minIO::cmsghdr)))

#define CMSG_DATA(cmsg) (reinterpret_cast<unsigned char *>(((struct minIO::cmsghdr *) (cmsg) + 1)))

#define CMSG_NXTHDR(mhdr, cmsg) __cmsg_nxthdr (mhdr, cmsg)

#define CMSG_LEN(len)   (CMSG_ALIGN ( sizeof(struct minIO::cmsghdr) ) + (len))

static inline struct cmsghdr * __cmsg_nxthdr (void *__ctl, struct cmsghdr *__cmsg) {
   return  reinterpret_cast<struct cmsghdr*>((((unsigned char *) __cmsg) + CMSG_ALIGN(__cmsg->cmsg_len)));
}

ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags){

    ssize_t ret { -1 };
    if(sockfd < 0 || msg == nullptr ) return ret;

    asm volatile (
        "\nmov %1, %%rax"
        "\nmov %2, %%rdi"
        "\nmov %3, %%rsi"
        "\nmov %4, %%rdx"
        "\nsyscall"
        "\nmov %%rax, %0"
        : "=r" (ret)
        : "i"  (0x2EULL),
          "r"  (static_cast<uint64_t>(sockfd)),
          "r"  (msg),
          "r"  (static_cast<uint64_t>(flags))
        : "%rax", "%rdi", "%rsi", "%rdx", "%rcx", "%r11", "memory");

    return ret;
}

int64_t pipe(int pipefd[2]){

    int64_t ret { -1 };
    if(pipefd == nullptr) return ret;

    asm volatile (
        "\nmov %1, %%rax"
        "\nmov %2, %%rdi"
        "\nsyscall"
        "\nmov %%rax, %0"
        : "=r" (ret)
        : "i"  (0x16ULL),
          "r"  (pipefd)
        : "%rax", "%rdi", "%rcx", "%r11", "memory");

    return ret;
}

enum SHUTDOWN_TYPE : uint32_t {
       SHUT_RD=0,
       SHUT_WR=1,
       SHUT_RDWR=2
};

int64_t shutdown(int sockfd, SHUTDOWN_TYPE type) noexcept {

    int64_t ret { -1 };
    if(sockfd < 0 ) return ret;

    asm volatile (
        "\nmov %1, %%rax"
        "\nmov %2, %%edi"
        "\nmov %3, %%esi"
        "\nsyscall"
        "\nmov %%rax, %0"
        : "=r" (ret)
        : "i"  (0x30ULL),
          "r"  (sockfd),
          "r"  (type)
        : "%rax", "%rdi", "%rsi", "%rcx", "%r11");

    return ret;
}

uint16_t htons(uint16_t in) noexcept {
   return ((in  & 0xff) << 8) | ((in >> 8) & 0xff);
}

void setIp(Sockaddr& in, uchar oct1, uchar oct2, uchar oct3, uchar oct4) noexcept {
   uchar* hdlr { reinterpret_cast<uchar*>(&(in.sin_addr)) };
   hdlr[0] = oct1;
   hdlr[1] = oct2;
   hdlr[2] = oct3;
   hdlr[3] = oct4;
}

#else
#error Unsupported Architecture
#endif

} // End Namespace
