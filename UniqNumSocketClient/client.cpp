#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <cstring>

#include <pthread.h>
using namespace std;

class ClientSocket{/*
private:
int sock;
struct sockaddr_in addr;
public:
void Connect(){
sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(1325);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }

  //  send(sock, message, sizeof(message), 0);
//    recv(sock, buf, 1024, 0);

  //  cout << buf << endl;
    close(sock);
} */
};

int main(int argc, char *argv[])
{
size_t posport,posmessage;
int buff;
string arguments,port,message;
ClientSocket Client;


for(int i = 0; i < argc;i++){
arguments.append(argv[i]);
}
posmessage=arguments.find("-m");

posport=arguments.find("-p");

if(posmessage!=arguments.npos)
{
message = arguments.substr(posmessage+2);
cout << message  <<  endl;
}
if(posport!=arguments.length()){
port = arguments.substr(posport+2,posmessage-posport-2);
if(port.length()>5){
cout << "Port out of range" << endl;
return 1;
}
cout << port << endl;

//cout << "PORT";
}

    return 0;
}
