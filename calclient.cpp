#include "cal.h"
using namespace std;
class ClientPacketHandler:public IPacketHandler{
	Transport& trans;
public:
	ClientPacketHandler(Transport& t):trans(t){
		this->trans=trans;
	}
    HPRetCode handlePacket(Packet *packet, void *args)
    {
    	cout<<"recv a response"<<endl;
        CalPacket *resPacket = (CalPacket*)packet;
	uint32_t res;
	cout<<resPacket->toString();
	resPacket->getRes(res);
	cout<<"id is:"<<resPacket->getChannelId()<<endl;
	cout<<"result is: "<<res<<endl;
	trans.stop();
        return IPacketHandler::FREE_CHANNEL;
    }    
};
class CalClient{
	Transport trans;
public:
	void start(string addr){
		cout<<"fake client start"<<endl;
		trans.start();
		CalPacketFactory packetFactory;
		ClientPacketHandler handler(trans);
		DefaultPacketStreamer ps(&packetFactory);
        	Connection* conns= trans.connect(addr.c_str(), &ps, true);
        	conns->setDefaultPacketHandler(&handler);
        	conns->setQueueLimit(500);
        	CalPacket *packet = new CalPacket(REQ);
		uint32_t op1=1;
		uint32_t op2=2;
		packet->setOp(op1,op2);
		cout<<"befor send:"<<"\n"
		    <<packet->toString()<<endl;
		if(conns->postPacket(packet)){
			cout<<"post ok"<<endl;
			cout<<packet->toString()<<endl;
		}else{
			cout<<"post faile"<<endl;
		}
		trans.wait();
	}
};
int main(){
	CalClient calClient;
	cout<<"Cal Client Starting"<<endl;
	string address="tcp:0.0.0.0:27001";
	calClient.start(address);
	cout<<"CalServer Exiting"<<endl;
	return 0;
}
