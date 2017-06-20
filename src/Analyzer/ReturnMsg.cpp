#include "ReturnMsg.h"

QString ReturnMsg::ERROR = "ERROR";
QString ReturnMsg::START = "START";
QString ReturnMsg::SUCCESS = "SUCCESS";
QString ReturnMsg::DELETE = "DELETE";
QString ReturnMsg::ASSIGN = "ASSIGN";

ReturnMsg::ReturnMsg(){
	this->msgType = "";
	this->msgContent = "";
}

ReturnMsg::~ReturnMsg(){

}
