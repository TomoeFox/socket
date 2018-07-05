#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <pthread.h>
using namespace std;
class NumFile {
private:
int num;
char Get[255];
string Path;
public:
NumFile(){
this->Path="/tmp/test";
}
~NumFile(){};
void Createfile(){
ofstream Create(Path);
Create.close();
cout << "File created!/n";
}
bool Openfile(){
ifstream Open(Path);
if(!Open.is_open()){
return false;
}
else {
return true;
}
Open.close();
}
void Getnum(){
ifstream Open(Path);
while(Open.good()){
Open.getline(Get,255,'\n');
num = atoi(Get);
}
Open.close();
}
int Gennum(){
ofstream Output;
Output.open(Path,fstream::app);
cout << "Gen new number!\n";
this->num++;
Output << "\n" << this->num;
cout << "Generated!\n";
return this->num;
}
};
class SocketServer : public NumFile{
private:
int serversock, clientsock;
int sizeaddr;
struct sockaddr_in client,server;
char buf[1024];
int bytes_read;
public:
string SendCode(int num){
string Code="Number is:";
Code.append(to_string(num));
return Code;
}
static void *proccesor(void * serversock) {
SocketServer Srv;
int sock = *(int*)serversock;
int readbyte;
char *servermessage, clientmessage[1024];

while((readbyte=recv(sock,clientmessage,1024,0))>0){
cout << clientmessage;
servermessage="Answere";
write(sock,servermessage,sizeof(servermessage));
close(sock);
}




if (readbyte==0){
cout << "Client disconnect\n";
}


}
void socket_work(){
    serversock = socket(AF_INET, SOCK_STREAM, 0);
    if(serversock < 0)
    {
cout << "Error socket\n";
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(1325);
    server.sin_addr.s_addr =INADDR_ANY;
    if(bind(serversock,(struct sockaddr *)&server, sizeof(server)) < 0){
        perror("bind");
        exit(2);}
    listen(serversock,10);
    sizeaddr = sizeof(struct sockaddr_in);
    pthread_t threadid;
    while((clientsock=accept(serversock,(struct sockaddr*)&client,(socklen_t*)&sizeaddr))){

     if(pthread_create(&threadid,NULL,proccesor,(void*)&clientsock)<0) {
     cout << "Multithreadin error\n";
     exit(2);
     }
    }
    if (clientsock < 0) {
    cout << "Accept error\n";
    exit(2);
    }

}
};
int main()
{
NumFile File;
if(!File.Openfile()){
cout << "Couldn`t find file, creating...";
File.Createfile();
}
else {
SocketServer Socket;
Socket.socket_work();
    return 0;
    }
}
