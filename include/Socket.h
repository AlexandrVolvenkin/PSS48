//-----------------------------------------------------------------------------------------------------
//  Sourse      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CSOCKET_H
#define CSOCKET_H

#include <stdint.h>

//-----------------------------------------------------------------------------------------------------
class CSocket
{
public:
    virtual uint8_t Select(void) = 0;
    virtual uint8_t Recv(uint8_t * , uint16_t ) = 0;
    virtual uint8_t Send(uint8_t * , uint16_t ) = 0;

protected:
private:
    uint8_t m_uiType;
    uint8_t m_uiInterface;

    friend class CUartSocket, CSpiSocket;
};

//-----------------------------------------------------------------------------------------------------
class CUartSocket : public CSocket
{
public:
    CUartSocket();
    virtual ~CUartSocket();
    uint8_t Connect(uint32_t ,
                    uint8_t ,
                    uint8_t ,
                    uint8_t  ,
                    uint8_t *,
                    uint8_t *) ;
    uint8_t Select(void);
    uint8_t Recv(uint8_t * );
    uint8_t Recv(uint8_t * , uint16_t );
    uint8_t Send(uint8_t * , uint16_t );

protected:
private:
    CUart m_xUart;
};

//-----------------------------------------------------------------------------------------------------
class CSpiSocket : public CSocket
{
public:
    CSpiSocket();
    virtual ~CSpiSocket();
    uint8_t Select(void);
    uint8_t Recv(uint8_t * , uint16_t );
    uint8_t Send(uint8_t * , uint16_t );

protected:
private:
    CSpi m_uiWatchDogStepIDxSpi;
};

//-----------------------------------------------------------------------------------------------------
#endif // CSOCKET_H




///* Historically, SOCKWQ_ASYNC_NOSPACE & SOCKWQ_ASYNC_WAITDATA were located
// * in sock->flags, but moved into sk->sk_wq->flags to be RCU protected.
// * Eventually all flags will be in sk->sk_wq->flags.
// */
//#define SOCKWQ_ASYNC_NOSPACE	0
//#define SOCKWQ_ASYNC_WAITDATA	1
//#define SOCK_NOSPACE		2
//#define SOCK_PASSCRED		3
//#define SOCK_PASSSEC		4
//
//#ifndef ARCH_HAS_SOCKET_TYPES
///**
// * enum sock_type - Socket types
// * @SOCK_STREAM: stream (connection) socket
// * @SOCK_DGRAM: datagram (conn.less) socket
// * @SOCK_RAW: raw socket
// * @SOCK_RDM: reliably-delivered message
// * @SOCK_SEQPACKET: sequential packet socket
// * @SOCK_DCCP: Datagram Congestion Control Protocol socket
// * @SOCK_PACKET: linux specific way of getting packets at the dev level.
// *		  For writing rarp and other similar things on the user level.
// *
// * When adding some new socket type please
// * grep ARCH_HAS_SOCKET_TYPE include/asm-* /socket.h, at least MIPS
// * overrides this enum for binary compat reasons.
// */
//enum sock_type
//{
//    SOCK_STREAM	= 1,
//    SOCK_DGRAM	= 2,
//    SOCK_RAW	= 3,
//    SOCK_RDM	= 4,
//    SOCK_SEQPACKET	= 5,
//    SOCK_DCCP	= 6,
//    SOCK_PACKET	= 10,
//};
//
//#define SOCK_MAX (SOCK_PACKET + 1)
///* Mask which covers at least up to SOCK_MASK-1.  The
// * remaining bits are used as flags. */
//#define SOCK_TYPE_MASK 0xf
//
///* Flags for socket, socketpair, accept4 */
//#define SOCK_CLOEXEC	O_CLOEXEC
//#ifndef SOCK_NONBLOCK
//#define SOCK_NONBLOCK	O_NONBLOCK
//#endif
//
//#endif /* ARCH_HAS_SOCKET_TYPES */
//
///**
// * enum sock_shutdown_cmd - Shutdown types
// * @SHUT_RD: shutdown receptions
// * @SHUT_WR: shutdown transmissions
// * @SHUT_RDWR: shutdown receptions/transmissions
// */
//enum sock_shutdown_cmd
//{
//    SHUT_RD,
//    SHUT_WR,
//    SHUT_RDWR,
//};
//
//struct socket_wq
//{
//    /* Note: wait MUST be first field of socket_wq */
//    wait_queue_head_t	wait;
//    struct fasync_struct	*fasync_list;
//    unsigned long		flags; /* %SOCKWQ_ASYNC_NOSPACE, etc */
//    struct rcu_head		rcu;
//} ____cacheline_aligned_in_smp;
//
///**
// *  struct socket - general BSD socket
// *  @state: socket state (%SS_CONNECTED, etc)
// *  @type: socket type (%SOCK_STREAM, etc)
// *  @flags: socket flags (%SOCK_NOSPACE, etc)
// *  @ops: protocol specific socket operations
// *  @file: File back pointer for gc
// *  @sk: internal networking protocol agnostic socket representation
// *  @wq: wait queue for several uses
// */
//struct socket
//{
//    socket_state		state;
//
//    short			type;
//
//    unsigned long		flags;
//
//    struct file		*file;
//    struct sock		*sk;
//    const struct proto_ops	*ops;
//
//    struct socket_wq	wq;
//};
