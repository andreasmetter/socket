/**
-connId: int
- address:Address
+invia()
+inviaRaw()
+ricevi()
+riceviRaw()
+~Connessione()

Il serverTCP ha il metodo accetta() che restituisce un Connessione*, perchè istanzia la Classe Connessione.
Ciò permette la multiconnessione, non si fa più sul socket, ma sulla connessione. es:(myConn1.ricevi()).
Il metodo close() sulla connessione è la distruzione della connessione.
Dentro Connessione si ha la accept. La send e la recv va nella connessione, non più sul server.
Nel clientTCP, ci sono i metodi inviaRaw e riceviRaw, che usano un sockID. Soluzione: anche il client, con il metodo connetti()
, si istanzia anche qua la connessione, passando come connID il sockID. In questo modo sparisce la send e la recv dal ClientTCP.
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
class SocketTCP{//superclasse di client e server che contiene metodi in comune
	protected:	int sockId;
	public:		SocketUDP();//socket()
				~SocketUDP();
				bool broadcast(bool broadcast); //setsockopt()
};

class ConnessioneTCP{
	private:	int connId;
			Address* address;
	public:	ConnessioneTCP(int connId, Address* address);
			~ConnessioneTCP();//shutdown()
			
			bool invia(char* msg);
			bool inviaRaw(void* msg, int length);//send()
			char* ricevi();
			void* riceviRaw(int* length);//recv()
};

class ServerTCP: public SocketTCP{	
	public: 	ServerTCP(int port, bool loopback); //bind(), listen();
			~ServerTCP();
			ConnessioneTCP* accetta(); //accept()
};

class ClientTCP: public SocketTCP{
	private: 	ConnessioneTCP* connessione;
	public:	ClientTCP(); //socket()
			~ClientTCP();
			
			bool connetti(Address* server); //connect()
			bool invia(char* msg);//saranno i wrapper dei metodi di sopra
			bool inviaRaw(void* msg, int length);
			char* ricevi();
			void* riceviRaw(int* length);
};

SocketTCP::SocketTCP(){
	this->sockId = socket(AF_INET, SOCK_STREAM,0);
}
SocketTCP::~SocketTCP(){
	//TODO: if per usare la shutdown 
}
bool SocketTCP::broadcast(bool broadcast){
	int len_so = sizeof(int);
	int val = status? 1: 0;
	return (setsockopt(this->sockId, SOL_SOCKET, SO_BROADCAST, &val, (socklen_t) len_so)==0);
}

ConnessioneTCP::ConnessioneTCP(int connId, Address* address){
	//da fare
}
bool ConnessioneTCP::invia(char* msg){
	int bufferLen;
	bufferLen = strlen(msg) + 1;

	return this->inviaRaw((void*) msg, bufferLen);
}
char* ConnessioneTCP::ricevi(){
	char* buffer;
	int ret = 0;

	buffer = (char*) this->riceviRaw(&ret);
	if(!buffer) return buffer;
	buffer[ret + 1] = '\0';
	return buffer;
}

bool ConnessioneTCP::inviaRaw(void* msg, int length){
	int sended = send(this->sockId, msg, length,0);
	if(sended != length){
		return true;
	}

	return false;
}

void* ConnessioneTCP::riceviRaw(int* length){
	void* buffer = malloc(MAX_MSG + 1);
	*length = recv(this->sockId, buffer, MAX_MSG, 0);

	printf("Ret vale:%d\n", length);
	if(*length <= 0){
		free(buffer);
		return NULL;
	}

	return buffer;
}

ServerTCP::ServerTCP(int port, bool loopback): SocketTCP(){

}

ServerTCP::~ServerTCP(){}

ConenssioneTCP* ServerTCP::accetta(){
}