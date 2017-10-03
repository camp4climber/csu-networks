//Lab6 Sock
//Jay DiFuria
//Tim Whitaker
//
////code sourced partially from http://googolflex.com/?p=322
//page info describing basic sockets w/ examples
#include<ctype.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<iostream>
#include<fstream>
#include<netinet/in.h>
#include<netdb.h>
#include<cstdlib>
#include<unistd.h>
#include<sstream>
#include<string.h>
using namespace std;

int main(int argc, char * argv [])
{
	int sock;
	struct sockaddr_in client;
	int PORT = 80;
	char *hostname = argv[1];
	struct hostent * host = gethostbyname(argv[1]);
	if((host == NULL) || (host->h_addr == NULL) )
	{
		cout << "Error grabbing DNS info" << endl;
		exit(1);
	}
	bzero(&client, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_port = htons( PORT );
	memcpy(&client.sin_addr, host->h_addr, host->h_length);
	sock=socket(AF_INET, SOCK_STREAM, 0);
	if(sock<0)
	{
		cout << "Error: Socket not created"<<endl;
		exit(1);
	}	
	if(connect(sock, (struct sockaddr*)&client,sizeof(client))<0)
	{	
		close(sock);
		cout<< "could not connect" << endl;
		exit(1);
	}
	string request = "GET /lab_docs/reset_instructions.pdf HTTP/1.0\n\n";
	request+=string(hostname);
	request += "\r\n\r\n";
	if(send(sock, request.c_str(), request.length(), 0) != (int)request.length())
	{
		cout << "Error in sending request" << endl;
		exit(1);
	}
	char cur;
	ofstream output;
	output.open("local_file");
	
	while(read(sock, &cur, 1) > 0)
	{
		output << cur;	
	}

	return 0;
}
