#ifndef _NETMANAGER_H_
#define _NETMANAGER_H_

#include "cocos2d.h"
#include"network\WebSocket.h"
#include"pb/msg.pb.h"
USING_NS_CC;



struct MsgPacket
{
	unsigned int datalen;
	unsigned int messageID;
	unsigned char  data[1024];
};

class NetManager : public cocos2d::network::WebSocket::Delegate
{
private:
	static NetManager* m_interface;
	NetManager();
public:
	

	~NetManager();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
	static	NetManager*GetInterface();

	network::WebSocket wb;


    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	virtual void onOpen(network::WebSocket* ws) ;
	/**
	* This function to be called when data has appeared from the server for the client connection.
	*
	* @param ws The WebSocket object connected.
	* @param data Data object for message.
	*/
	virtual void onMessage(network::WebSocket* ws, const network::WebSocket::Data& data) ;
	/**
	* When the WebSocket object connected wants to close or the protocol won't get used at all and current _readyState is State::CLOSING,this function is to be called.
	*
	* @param ws The WebSocket object connected.
	*/
	virtual void onClose(network::WebSocket* ws);
	/**
	* This function is to be called in the following cases:
	* 1. client connection is failed.
	* 2. the request client connection has been unable to complete a handshake with the remote server.
	* 3. the protocol won't get used at all after this callback and current _readyState is State::CONNECTING.
	* 4. when a socket descriptor needs to be removed from an external polling array. in is again the struct libwebsocket_pollargs containing the fd member to be removed. If you are using the internal polling loop, you can just ignore it and current _readyState is State::CONNECTING.
	*
	* @param ws The WebSocket object connected.
	* @param error WebSocket::ErrorCode enum,would be ErrorCode::TIME_OUT or ErrorCode::CONNECTION_FAILURE.
	*/
	virtual void onError(network::WebSocket* ws, const network::WebSocket::ErrorCode& error) ;

    // implement the "static create()" method manually
    //提供一个封包与解包的方法


	MsgPacket*Packages(int msgID,google::protobuf::Message*msg); //封包
	MsgPacket*Unpacking(unsigned char*data, int datalen);//解包
	
};

#endif // __HELLOWORLD_SCENE_H__
