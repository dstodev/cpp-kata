#include <exceptions.hxx>
#include <gtest/gtest.h>
#include <string>

using std::string;

#define ExceptionTest(Type, enumeration, message)          \
	TEST(RunawayWindowsExceptions, Type)                   \
	{                                                      \
		Type uut;                                          \
		ASSERT_STREQ(message, uut.what());                 \
		ASSERT_THROW(map_to_exception(enumeration), Type); \
	}                                                      \
	static_assert(true, "force semicolon after macro")

// clang-format off
ExceptionTest(WsaInvalidHandle, WSA_INVALID_HANDLE,
              "Specified event object handle is invalid.\nAn application attempts to use an event object, but the specified handle is not valid.");
ExceptionTest(WsaNotEnoughMemory, WSA_NOT_ENOUGH_MEMORY,
              "Insufficient memory available.\nAn application used a Windows Sockets function that directly maps to a Windows function. The Windows function is indicating a lack of required memory resources.");
ExceptionTest(WsaInvalidParameter, WSA_INVALID_PARAMETER,
              "One or more parameters are invalid.\nAn application used a Windows Sockets function which directly maps to a Windows function. The Windows function is indicating a problem with one or more parameters.");
ExceptionTest(WsaOperationAborted, WSA_OPERATION_ABORTED,
              "Overlapped operation aborted.\nAn overlapped operation was canceled due to the closure of the socket, or the execution of the SIO_FLUSH command in WSAIoctl.");
ExceptionTest(WsaIoIncomplete, WSA_IO_INCOMPLETE,
              "Overlapped I/O event object not in signaled state.\nThe application has tried to determine the status of an overlapped operation which is not yet completed. Applications that use WSAGetOverlappedResult (with the fWait flag set to FALSE) in a polling mode to determine when an overlapped operation has completed, get this error code until the operation is complete.");
ExceptionTest(WsaIoPending, WSA_IO_PENDING,
              "Overlapped operations will complete later.\nThe application has initiated an overlapped operation that cannot be completed immediately. A completion indication will be given later when the operation has been completed.");
ExceptionTest(WsaEIntr, WSAEINTR,
              "Interrupted function call.\nA blocking operation was interrupted by a call to WSACancelBlockingCall.");
ExceptionTest(WsaEBadF, WSAEBADF,
              "File handle is not valid.\nThe file handle supplied is not valid.");
ExceptionTest(WsaEAcces, WSAEACCES,
              "Permission denied.\nAn attempt was made to access a socket in a way forbidden by its access permissions. An example is using a broadcast address for sendto without broadcast permission being set using setsockopt(SO_BROADCAST).\nAnother possible reason for the WSAEACCES error is that when the bind function is called (on Windows NT 4.0 with SP4 and later), another application, service, or kernel mode driver is bound to the same address with exclusive access. Such exclusive access is a new feature of Windows NT 4.0 with SP4 and later, and is implemented by using the SO_EXCLUSIVEADDRUSE option.");
ExceptionTest(WsaEFault, WSAEFAULT,
              "Bad address.\nThe system detected an invalid pointer address in attempting to use a pointer argument of a call. This error occurs if an application passes an invalid pointer value, or if the length of the buffer is too small. For instance, if the length of an argument, which is a sockaddr structure, is smaller than the sizeof(sockaddr).");
ExceptionTest(WsaEInval, WSAEINVAL,
              "Invalid argument.\nSome invalid argument was supplied (for example, specifying an invalid level to the setsockopt function). In some instances, it also refers to the current state of the socket—for instance, calling accept on a socket that is not listening.");
ExceptionTest(WsaEMFile, WSAEMFILE,
              "Too many open files.\nToo many open sockets. Each implementation may have a maximum number of socket handles available, either globally, per process, or per thread.");
ExceptionTest(WsaEWouldBlock, WSAEWOULDBLOCK,
              "Resource temporarily unavailable.\nThis error is returned from operations on nonblocking sockets that cannot be completed immediately, for example recv when no data is queued to be read from the socket. It is a nonfatal error, and the operation should be retried later. It is normal for WSAEWOULDBLOCK to be reported as the result from calling connect on a nonblocking SOCK_STREAM socket, since some time must elapse for the connection to be established.");
ExceptionTest(WsaEInProgress, WSAEINPROGRESS,
              "Operation now in progress.\nA blocking operation is currently executing. Windows Sockets only allows a single blocking operation—per- task or thread—to be outstanding, and if any other function call is made (whether or not it references that or any other socket) the function fails with the WSAEINPROGRESS error.");
ExceptionTest(WsaEAlready, WSAEALREADY,
              "Operation already in progress.\nAn operation was attempted on a nonblocking socket with an operation already in progress—that is, calling connect a second time on a nonblocking socket that is already connecting, or canceling an asynchronous request (WSAAsyncGetXbyY) that has already been canceled or completed.");
ExceptionTest(WsaENotSock, WSAENOTSOCK,
              "Socket operation on nonsocket.\nAn operation was attempted on something that is not a socket. Either the socket handle parameter did not reference a valid socket, or for select, a member of an fd_set was not valid.");
ExceptionTest(WsaEDestAddrReq, WSAEDESTADDRREQ,
              "Destination address required.\nA required address was omitted from an operation on a socket. For example, this error is returned if sendto is called with the remote address of ADDR_ANY.");
ExceptionTest(WsaEMsgSize, WSAEMSGSIZE,
              "Message too long.\nA message sent on a datagram socket was larger than the internal message buffer or some other network limit, or the buffer used to receive a datagram was smaller than the datagram itself.");
ExceptionTest(WsaEProtoType, WSAEPROTOTYPE,
              "Protocol wrong type for socket.\nA protocol was specified in the socket function call that does not support the semantics of the socket type requested. For example, the ARPA Internet UDP protocol cannot be specified with a socket type of SOCK_STREAM.");
ExceptionTest(WsaENoProtoOpt, WSAENOPROTOOPT,
              "Bad protocol option.\nAn unknown, invalid or unsupported option or level was specified in a getsockopt or setsockopt call.");
ExceptionTest(WsaEProtoNoSupport, WSAEPROTONOSUPPORT,
              "Protocol not supported.\nThe requested protocol has not been configured into the system, or no implementation for it exists. For example, a socket call requests a SOCK_DGRAM socket, but specifies a stream protocol.");
ExceptionTest(WsaESockTNoSupport, WSAESOCKTNOSUPPORT,
              "Socket type not supported.\nThe support for the specified socket type does not exist in this address family. For example, the optional type SOCK_RAW might be selected in a socket call, and the implementation does not support SOCK_RAW sockets at all.");
ExceptionTest(WsaEOpNotSupp, WSAEOPNOTSUPP,
              "Operation not supported.\nThe attempted operation is not supported for the type of object referenced. Usually this occurs when a socket descriptor to a socket that cannot support this operation is trying to accept a connection on a datagram socket.");
ExceptionTest(WsaEPFNoSupport, WSAEPFNOSUPPORT,
              "Protocol family not supported.\nThe protocol family has not been configured into the system or no implementation for it exists. This message has a slightly different meaning from WSAEAFNOSUPPORT. However, it is interchangeable in most cases, and all Windows Sockets functions that return one of these messages also specify WSAEAFNOSUPPORT.");
ExceptionTest(WsaEAFNoSupport, WSAEAFNOSUPPORT,
              "Address family not supported by protocol family.\nAn address incompatible with the requested protocol was used. All sockets are created with an associated address family (that is, AF_INET for Internet Protocols) and a generic protocol type (that is, SOCK_STREAM). This error is returned if an incorrect protocol is explicitly requested in the socket call, or if an address of the wrong family is used for a socket, for example, in sendto.");
ExceptionTest(WsaEAddrInUse, WSAEADDRINUSE,
              "Address already in use.\nTypically, only one usage of each socket address (protocol/IP address/port) is permitted. This error occurs if an application attempts to bind a socket to an IP address/port that has already been used for an existing socket, or a socket that was not closed properly, or one that is still in the process of closing. For server applications that need to bind multiple sockets to the same port number, consider using setsockopt (SO_REUSEADDR). Client applications usually need not call bind at all—connect chooses an unused port automatically. When bind is called with a wildcard address (involving ADDR_ANY), a WSAEADDRINUSE error could be delayed until the specific address is committed. This could happen with a call to another function later, including connect, bind, WSAConnect, or WSAJoinLeaf.");
ExceptionTest(WsaEAddrNotAvail, WSAEADDRNOTAVAIL,
              "Cannot assign requested address.\nThe requested address is not valid in its context. This normally results from an attempt to bind to an address that is not valid for the local computer. This can also result from connect, sendto, WSAConnect, WSAJoinLeaf, or WSASendTo when the remote address or port is not valid for a remote computer (for example, address or port 0).");
ExceptionTest(WsaENetDown, WSAENETDOWN,
              "Network is down.\nA socket operation encountered a dead network. This could indicate a serious failure of the network system (that is, the protocol stack that the Windows Sockets DLL runs over), the network interface, or the local network itself.");
ExceptionTest(WsaENetUnreach, WSAENETUNREACH,
              "Network is unreachable.\nA socket operation was attempted to an unreachable network. This usually means the local software knows no route to reach the remote host.");
ExceptionTest(WsaENetReset, WSAENETRESET,
              "Network dropped connection on reset.\nThe connection has been broken due to keep-alive activity detecting a failure while the operation was in progress. It can also be returned by setsockopt if an attempt is made to set SO_KEEPALIVE on a connection that has already failed.");
ExceptionTest(WsaEConnAborted, WSAECONNABORTED,
              "Software caused connection abort.\nAn established connection was aborted by the software in your host computer, possibly due to a data transmission time-out or protocol error.");
ExceptionTest(WsaEConnReset, WSAECONNRESET,
              "Connection reset by peer.\nAn existing connection was forcibly closed by the remote host. This normally results if the peer application on the remote host is suddenly stopped, the host is rebooted, the host or remote network interface is disabled, or the remote host uses a hard close (see setsockopt for more information on the SO_LINGER option on the remote socket). This error may also result if a connection was broken due to keep-alive activity detecting a failure while one or more operations are in progress. Operations that were in progress fail with WSAENETRESET. Subsequent operations fail with WSAECONNRESET.");
ExceptionTest(WsaENoBufS, WSAENOBUFS,
              "No buffer space available.\nAn operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full.");
ExceptionTest(WsaEIsConn, WSAEISCONN,
              "Socket is already connected.\nA connect request was made on an already-connected socket. Some implementations also return this error if sendto is called on a connected SOCK_DGRAM socket (for SOCK_STREAM sockets, the to parameter in sendto is ignored) although other implementations treat this as a legal occurrence.");
ExceptionTest(WsaENotConn, WSAENOTCONN,
              "Socket is not connected.\nA request to send or receive data was disallowed because the socket is not connected and (when sending on a datagram socket using sendto) no address was supplied. Any other type of operation might also return this error—for example, setsockopt setting SO_KEEPALIVE if the connection has been reset.");
ExceptionTest(WsaEShutdown, WSAESHUTDOWN,
              "Cannot send after socket shutdown.\nA request to send or receive data was disallowed because the socket had already been shut down in that direction with a previous shutdown call. By calling shutdown a partial close of a socket is requested, which is a signal that sending or receiving, or both have been discontinued.");
ExceptionTest(WsaETooManyRefs, WSAETOOMANYREFS,
              "Too many references.\nToo many references to some kernel object.");
ExceptionTest(WsaETimedOut, WSAETIMEDOUT,
              "Connection timed out.\nA connection attempt failed because the connected party did not properly respond after a period of time, or the established connection failed because the connected host has failed to respond.");
ExceptionTest(WsaEConnRefused, WSAECONNREFUSED,
              "Connection refused.\nNo connection could be made because the target computer actively refused it. This usually results from trying to connect to a service that is inactive on the foreign host—that is, one with no server application running.");
ExceptionTest(WsaELoop, WSAELOOP,
              "Cannot translate name.\nCannot translate a name.");
ExceptionTest(WsaENameTooLong, WSAENAMETOOLONG,
              "Name too long.\nA name component or a name was too long.");
ExceptionTest(WsaEHostDown, WSAEHOSTDOWN,
              "Host is down.\nA socket operation failed because the destination host is down. A socket operation encountered a dead host. Networking activity on the local host has not been initiated. These conditions are more likely to be indicated by the error WSAETIMEDOUT.");
ExceptionTest(WsaEHostUnreach, WSAEHOSTUNREACH,
              "No route to host.\nA socket operation was attempted to an unreachable host. See WSAENETUNREACH.");
ExceptionTest(WsaENotEmpty, WSAENOTEMPTY,
              "Directory not empty.\nCannot remove a directory that is not empty.");
ExceptionTest(WsaEProcLim, WSAEPROCLIM,
              "Too many processes.\nA Windows Sockets implementation may have a limit on the number of applications that can use it simultaneously. WSAStartup may fail with this error if the limit has been reached.");
ExceptionTest(WsaEUsers, WSAEUSERS,
              "User quota exceeded.\nRan out of user quota.");
ExceptionTest(WsaEDQuot, WSAEDQUOT,
              "Disk quota exceeded.\nRan out of disk quota.");
ExceptionTest(WsaEStale, WSAESTALE,
              "Stale file handle reference.\nThe file handle reference is no longer available.");
ExceptionTest(WsaERemote, WSAEREMOTE,
              "Item is remote.\nThe item is not available locally.");
ExceptionTest(WsaSysNotReady, WSASYSNOTREADY,
              "Network subsystem is unavailable.\nThis error is returned by WSAStartup if the Windows Sockets implementation cannot function at this time because the underlying system it uses to provide network services is currently unavailable. Users should check:\nThat the appropriate Windows Sockets DLL file is in the current path.\nThat they are not trying to use more than one Windows Sockets implementation simultaneously. If there is more than one Winsock DLL on your system, be sure the first one in the path is appropriate for the network subsystem currently loaded.\nThe Windows Sockets implementation documentation to be sure all necessary components are currently installed and configured correctly.");
ExceptionTest(WsaVerNotSupported, WSAVERNOTSUPPORTED,
              "Winsock.dll version out of range.\nThe current Windows Sockets implementation does not support the Windows Sockets specification version requested by the application. Check that no old Windows Sockets DLL files are being accessed.");
ExceptionTest(WsaNotInitialized, WSANOTINITIALISED,
              "Successful WSAStartup not yet performed.\nEither the application has not called WSAStartup or WSAStartup failed. The application may be accessing a socket that the current active task does not own (that is, trying to share a socket between tasks), or WSACleanup has been called too many times.");
ExceptionTest(WsaEDiscon, WSAEDISCON,
              "Graceful shutdown in progress.\nReturned by WSARecv and WSARecvFrom to indicate that the remote party has initiated a graceful shutdown sequence.");
ExceptionTest(WsaENoMore, WSAENOMORE,
              "No more results.\nNo more results can be returned by the WSALookupServiceNext function.");
ExceptionTest(WsaECancelled, WSAECANCELLED,
              "Call has been canceled.\nA call to the WSALookupServiceEnd function was made while this call was still processing. The call has been canceled.");
ExceptionTest(WsaEInvalidProcTable, WSAEINVALIDPROCTABLE,
              "Procedure call table is invalid.\nThe service provider procedure call table is invalid. A service provider returned a bogus procedure table to Ws2_32.dll. This is usually caused by one or more of the function pointers being NULL.");
ExceptionTest(WsaEInvalidProvider, WSAEINVALIDPROVIDER,
              "Service provider is invalid.\nThe requested service provider is invalid. This error is returned by the WSCGetProviderInfo and WSCGetProviderInfo32 functions if the protocol entry specified could not be found. This error is also returned if the service provider returned a version number other than 2.0.");
ExceptionTest(WsaEProviderFailedInit, WSAEPROVIDERFAILEDINIT,
              "Service provider failed to initialize.\nThe requested service provider could not be loaded or initialized. This error is returned if either a service provider's DLL could not be loaded (LoadLibrary failed) or the provider's WSPStartup or NSPStartup function failed.");
ExceptionTest(WsaSysCallFailure, WSASYSCALLFAILURE,
              "System call failure.\nA system call that should never fail has failed. This is a generic error code, returned under various conditions.\nReturned when a system call that should never fail does fail. For example, if a call to WaitForMultipleEvents fails or one of the registry functions fails trying to manipulate the protocol/namespace catalogs.\nReturned when a provider does not return SUCCESS and does not provide an extended error code. Can indicate a service provider implementation error.");
ExceptionTest(WsaServiceNotFound, WSASERVICE_NOT_FOUND,
              "Service not found.\nNo such service is known. The service cannot be found in the specified name space.");
ExceptionTest(WsaTypeNotFound, WSATYPE_NOT_FOUND,
              "Class type not found.\nThe specified class was not found.");
ExceptionTest(WsaENoMore2, WSA_E_NO_MORE,
              "No more results.\nNo more results can be returned by the WSALookupServiceNext function.");
ExceptionTest(WsaECancelled2, WSA_E_CANCELLED,
              "Call was canceled.\nA call to the WSALookupServiceEnd function was made while this call was still processing. The call has been canceled.");
ExceptionTest(WsaERefused, WSAEREFUSED,
              "Database query was refused.\nA database query failed because it was actively refused.");
ExceptionTest(WsaHostNotFound, WSAHOST_NOT_FOUND,
              "Host not found.\nNo such host is known. The name is not an official host name or alias, or it cannot be found in the database(s) being queried. This error may also be returned for protocol and service queries, and means that the specified name could not be found in the relevant database.");
ExceptionTest(WsaTryAgain, WSATRY_AGAIN,
              "Nonauthoritative host not found.\nThis is usually a temporary error during host name resolution and means that the local server did not receive a response from an authoritative server. A retry at some time later may be successful.");
ExceptionTest(WsaNoRecovery, WSANO_RECOVERY,
              "This is a nonrecoverable error.\nThis indicates that some sort of nonrecoverable error occurred during a database lookup. This may be because the database files (for example, BSD-compatible HOSTS, SERVICES, or PROTOCOLS files) could not be found, or a DNS request was returned by the server with a severe error.");
ExceptionTest(WsaNoData, WSANO_DATA,
              "Valid name, no data record of requested type.\nThe requested name is valid and was found in the database, but it does not have the correct associated data being resolved for. The usual example for this is a host name-to-address translation attempt (using gethostbyname or WSAAsyncGetHostByName) which uses the DNS (Domain Name Server). An MX record is returned but no A record—indicating the host itself exists, but is not directly reachable.");
ExceptionTest(WsaQosReceivers, WSA_QOS_RECEIVERS,
              "QoS receivers.\nAt least one QoS reserve has arrived.");
ExceptionTest(WsaQosSenders, WSA_QOS_SENDERS,
              "QoS senders.\nAt least one QoS send path has arrived.");
ExceptionTest(WsaQosNoSenders, WSA_QOS_NO_SENDERS,
              "No QoS senders.\nThere are no QoS senders.");
ExceptionTest(WsaQosNoReceivers, WSA_QOS_NO_RECEIVERS,
              "QoS no receivers.\nThere are no QoS receivers.");
ExceptionTest(WsaQosRequestConfirmed, WSA_QOS_REQUEST_CONFIRMED,
              "QoS request confirmed.\nThe QoS reserve request has been confirmed.");
ExceptionTest(WsaQosAdmissionFailure, WSA_QOS_ADMISSION_FAILURE,
              "QoS admission error.\nA QoS error occurred due to lack of resources.");
ExceptionTest(WsaQosPolicyFailure, WSA_QOS_POLICY_FAILURE,
              "QoS policy failure.\nThe QoS request was rejected because the policy system couldn't allocate the requested resource within the existing policy.");
ExceptionTest(WsaQosBadStyle, WSA_QOS_BAD_STYLE,
              "QoS bad style.\nAn unknown or conflicting QoS style was encountered.");
ExceptionTest(WsaQosBadObject, WSA_QOS_BAD_OBJECT,
              "QoS bad object.\nA problem was encountered with some part of the filterspec or the provider-specific buffer in general.");
ExceptionTest(WsaQosTrafficCtrlError, WSA_QOS_TRAFFIC_CTRL_ERROR,
              "QoS traffic control error.\nAn error with the underlying traffic control (TC) API as the generic QoS request was converted for local enforcement by the TC API. This could be due to an out of memory error or to an internal QoS provider error.");
ExceptionTest(WsaQosGenericError, WSA_QOS_GENERIC_ERROR,
              "QoS generic error.\nA general QoS error.");
ExceptionTest(WsaQosEServiceType, WSA_QOS_ESERVICETYPE,
              "QoS service type error.\nAn invalid or unrecognized service type was found in the QoS flowspec.");
ExceptionTest(WsaQosEFlowspec, WSA_QOS_EFLOWSPEC,
              "QoS flowspec error.\nAn invalid or inconsistent flowspec was found in the QOS structure.");
ExceptionTest(WsaQosEProvSpecBuf, WSA_QOS_EPROVSPECBUF,
              "Invalid QoS provider buffer.\nAn invalid QoS provider-specific buffer.");
ExceptionTest(WsaQosEFilterStyle, WSA_QOS_EFILTERSTYLE,
              "Invalid QoS filter style.\nAn invalid QoS filter style was used.");
ExceptionTest(WsaQosEFilterType, WSA_QOS_EFILTERTYPE,
              "Invalid QoS filter type.\nAn invalid QoS filter type was used.");
ExceptionTest(WsaQosEFilterCount, WSA_QOS_EFILTERCOUNT,
              "Incorrect QoS filter count.\nAn incorrect number of QoS FILTERSPECs were specified in the FLOWDESCRIPTOR.");
ExceptionTest(WsaQosEObjLength, WSA_QOS_EOBJLENGTH,
              "Invalid QoS object length.\nAn object with an invalid ObjectLength field was specified in the QoS provider-specific buffer.");
ExceptionTest(WsaQosEFlowCount, WSA_QOS_EFLOWCOUNT,
              "Incorrect QoS flow count.\nAn incorrect number of flow descriptors was specified in the QoS structure.");
ExceptionTest(WsaQosEUnknownPsObj, WSA_QOS_EUNKNOWNPSOBJ,
              "Unrecognized QoS object.\nAn unrecognized object was found in the QoS provider-specific buffer.");
ExceptionTest(WsaQosEPolicyObj, WSA_QOS_EPOLICYOBJ,
              "Invalid QoS policy object.\nAn invalid policy object was found in the QoS provider-specific buffer.");
ExceptionTest(WsaQosEFlowDesc, WSA_QOS_EFLOWDESC,
              "Invalid QoS flow descriptor.\nAn invalid QoS flow descriptor was found in the flow descriptor list.");
ExceptionTest(WsaQosEPsFlowspec, WSA_QOS_EPSFLOWSPEC,
              "Invalid QoS provider-specific flowspec.\nAn invalid or inconsistent flowspec was found in the QoS provider-specific buffer.");
ExceptionTest(WsaQosEPsFilterSpec, WSA_QOS_EPSFILTERSPEC,
              "Invalid QoS provider-specific filterspec.\nAn invalid FILTERSPEC was found in the QoS provider-specific buffer.");
ExceptionTest(WsaQosESDModeObj, WSA_QOS_ESDMODEOBJ,
              "Invalid QoS shape discard mode object.\nAn invalid shape discard mode object was found in the QoS provider-specific buffer.");
ExceptionTest(WsaQosEShapeRateObj, WSA_QOS_ESHAPERATEOBJ,
              "Invalid QoS shaping rate object.\nAn invalid shaping rate object was found in the QoS provider-specific buffer.");
ExceptionTest(WsaQosReservedPEType, WSA_QOS_RESERVED_PETYPE,
              "Reserved policy QoS element type.\nA reserved policy element was found in the QoS provider-specific buffer.");
// clang-format on