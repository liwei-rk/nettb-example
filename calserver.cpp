#include "tbnet.h"
#include "cal.h"

using namespace tbnet;
using namespace std;


class CalServerAdapter : public IServerAdapter
{
public:
    IPacketHandler::HPRetCode handlePacket(Connection *connection, Packet *packet)
    {
    	cout<<"server recv a packet"<<endl;
        CalPacket *reply = new CalPacket(RES);
	uint32_t op1,op2;
	((CalPacket*) packet)->getOp(op1,op2);
	reply->setRes(op1+op2);
	uint32_t res;
	reply->getRes(res);
        reply->setChannelId(packet->getChannelId());
	cout<<reply->toString();
        if (connection->postPacket(reply) == false) {
            reply->free();
        }else{
		cout<<"return to client ok"<<endl;
	}
        packet->free();
        return IPacketHandler::FREE_CHANNEL;
    }    
};
void singalHandler(int sig)
{
    if (sig==3) {
        TBNET_GLOBAL_STAT.log();
        TBNET_GLOBAL_STAT.clear();
    } else if (sig == 4) {
        assert(false);
    } else {
    }
}
class CalServer{
	Transport trans;
	
	public: void start(string address){
		trans.start();
		CalPacketFactory packetFactory;
		DefaultPacketStreamer ps(&packetFactory);
		CalServerAdapter adaptor;
		cout<<address<<endl;

		IOComponent *ioc=trans.listen(address.c_str(),&ps,&adaptor);
		if(ioc==NULL){
			cout<<"init transport error"<<endl;
			return;
		}
		//trans.wait();
		if(trans.wait()){
			cout<<"wait successful"<<endl;
		}
	}
};

int main(){
	CalServer calServer;
	cout<<"CalServer starting!"<<endl;
	string address="tcp:0.0.0.0:27001";
	calServer.start(address);
	cout<<"CalServer Exiting!"<<endl;
}
