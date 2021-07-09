#include"NetManager.h"

NetManager*NetManager::m_interface = NULL;
NetManager::NetManager()
{
}

NetManager::~NetManager()
{
}

NetManager * NetManager::GetInterface()
{
	
	if (m_interface == NULL) {

		m_interface = new NetManager();
		m_interface->init();

	}

	return m_interface;
}

bool NetManager::init()
{
	 
	if (wb.init(*(network::WebSocket::Delegate*)this, "192.168.2.87:8080")) {
		return true;
	}
	return false;
}

void NetManager::onOpen(network::WebSocket * ws)
{
	

}

void NetManager::onMessage(network::WebSocket * ws, const network::WebSocket::Data & data)
{
	MsgPacket*_MP= Unpacking((unsigned char*)data.bytes, data.len);
	if (_MP == NULL) return;
	switch (_MP->messageID)
	{
	case 203:
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("Login", (void*)_MP);
		break;
	case 200:
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("chat", (void*)_MP);
		break;
	case 204:
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("OnTeamMsg", (void*)_MP);
		break;
	case 205:
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("OnAddTeams", (void*)_MP);
		break;
	default:
		break;
	} 
	
}

void NetManager::onClose(network::WebSocket * ws)
{
}

void NetManager::onError(network::WebSocket * ws, const network::WebSocket::ErrorCode & error)
{
}

MsgPacket * NetManager::Packages(int msgID, google::protobuf::Message * msg)
{
	MsgPacket*_Nmsg=new MsgPacket();
	_Nmsg->messageID = msgID;
	_Nmsg->datalen = msg->ByteSize();
	unsigned char*buff=new unsigned char[_Nmsg->datalen];
	msg->SerializePartialToArray(buff, _Nmsg->datalen);
	memcpy(_Nmsg->data, buff, _Nmsg->datalen);

	return _Nmsg;

	
}

MsgPacket * NetManager::Unpacking(unsigned char*data,int datalen)
{
	MsgPacket*_Nmsg = new MsgPacket();
	memcpy(_Nmsg, data,datalen);

	return _Nmsg;

	
}
