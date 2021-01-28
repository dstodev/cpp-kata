#include "server.hxx"
#include <memory>

using std::move;
using std::ref;
using std::string;
using std::thread;
using std::unique_ptr;

Server::Server()
    : _sock(INVALID_SOCKET)
    , _hints()
    , _wsa(WsaWrapper::get_instance())
{
	ZeroMemory(&_hints, sizeof(_hints));
	_hints.ai_family = AF_UNSPEC;
	_hints.ai_socktype = SOCK_STREAM;
	_hints.ai_protocol = IPPROTO_TCP;
}

Server::~Server()
{
	closesocket(_sock);
}

string Server::receive(SOCKET client) const
{
	return string();
}

void Server::send(SOCKET client, string message) const
{}

void Server::bind(const char * port)
{
	int status;

	// Set AI_PASSIVE
	_hints.ai_flags |= AI_PASSIVE;

	// Resolve port
	struct addrinfo * result;
	status = getaddrinfo(nullptr, port, &_hints, &result);
	if (status != 0) {
		map_to_exception(status);
	}

	// Create a socket to bind with
	SOCKET sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (sock == INVALID_SOCKET) {
		status = WSAGetLastError();
		map_to_exception(status);
	}

	// Bind to socket
	status = ::bind(sock, result->ai_addr, (int) result->ai_addrlen);
	if (status == SOCKET_ERROR) {
		status = WSAGetLastError();
		freeaddrinfo(result);
		map_to_exception(status);
	}

	freeaddrinfo(result);
	_sock = sock;

	// Set non-blocking mode on the socket
	set_blocking(false);
}

void Server::listen(size_t max_queue)
{
	int status;

	status = ::listen(_sock, max_queue);
	if (status == SOCKET_ERROR) {
		status = WSAGetLastError();
		map_to_exception(status);
	}
}

void Server::set_blocking(bool mode)
{
	DWORD bytes;
	auto converted_mode = static_cast<unsigned long>(!mode);
	int status = WSAIoctl(_sock,
	                      FIONBIO,
	                      &converted_mode,
	                      sizeof(converted_mode),
	                      nullptr,
	                      0,
	                      &bytes,
	                      nullptr,
	                      nullptr);

	if (status == SOCKET_ERROR) {
		status = WSAGetLastError();
		map_to_exception(status);
	}
}