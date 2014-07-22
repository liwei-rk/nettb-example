#ifndef CAL_H
#define CAL_H
#include "tbnet.h"
#include<sstream>
#define REQ 1
#define RES 2
using namespace tbnet;
using namespace std;
class CalPacket :public Packet{
public:
	CalPacket(int pcode){
		setPCode(pcode);
		//setChannelId(4);
	}
	bool encode(DataBuffer* output){
		switch(getPCode()){
			case REQ:output->writeInt32(op1);
				 output->writeInt32(op2);
				 break;
			case RES:output->writeInt32(res);
		}
		return true;
	}
	bool decode(DataBuffer* input,PacketHeader* header){
		switch(getPCode()){
			case REQ:op1=input->readInt32();
				 op2=input->readInt32();
				 break;
		        case RES:res=input->readInt32();
				 res=3;
		}
		return true;
	}
	void setOp(uint32_t op1,uint32_t op2){
		this->op1=op1;
		this->op2=op2;
	}
	void setRes(uint32_t res){
		this->res=res;
	}
	void getOp(uint32_t& op1,uint32_t&op2){
		op1=this->op1;
		op2=this->op2;
	}
	void getRes(uint32_t &res){
		res=this->res;
	}
	string toString(){
		stringstream ss;
		ss<<"type:"<<getPCode()<<"\n"
		  <<"op1 :"<<op1<<"\n"
		  <<"op2 :"<<op2<<"\n"
		  <<"res :"<<res<<endl
		  <<"id  :"<<getChannelId()<<endl;
		 return ss.str();
	}
	private:
		uint32_t op1;
		uint32_t op2;
		uint32_t res;
};
class CalPacketFactory:public IPacketFactory{
public:
    Packet *createPacket(int pcode)
    {
        return new CalPacket(pcode);
    }
};
#endif //CAL_H
