#include "socketTCP.hpp"

int main(int argc, char const *argv[])
{
	if(argc!=4){
		printf("USAGE: %s PORT LOOPBACK(0 true) MSG\n", argv[0]);
		return -1;
	}
	char* msg = argv[3];
	bool loop = false;
	if(atoi(argv[2])==0){
		loop = true;
	}
	int port = atoi(argv[1]);
	ServerTCP* server = new ServerTCP(port,loop);
	Connessione* conn = server->accetta();
	printf("connessione accettata.\n");
	char* ricevuto = conn->ricevi();
	printf("ho ricevuto: %s\n",ricevuto);
	if(!conn->invia(msg)){
		printf("errore invio\n");
		return -2;
	}

	printf("chiudo connessione.\n");
	delete(conn);
	printf("chiudo socket.\n");
	delete(server);
	return 0;
}