#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <cstring>
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
int sock, listener;
struct sockaddr_in addr;
char buf[1024];
int bytes_read;
public:
string SendCode(int num){
string Code="Number is:";
Code.append(to_string(num));
return Code;
}
void socket_work(){
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1325);
    addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        perror("bind");
        exit(2);}
    listen(listener, 1);
    while(true){
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
    perror("accept");
    exit(3);
        }
        switch(fork())
        {
        case -1:
            perror("fork");
            break;
        case 0:
            close(listener);
            while(1)
            {
                bytes_read = recv(sock, buf, 1024, 0);
                if(bytes_read <= 0) break;
                sendnumber();
            }

            close(sock);
            _exit(0);

        default:
            close(sock);

        }
    }
    close(listener);
}
void sendnumber(){
Getnum();
strcpy(buf,SendCode(Gennum()).c_str());
send(sock, buf, sizeof(buf), 0);
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
