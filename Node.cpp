#include "Node.h"

Node::Node(Stock item){
    data = new Stock(item);
    next = NULL;
};
Node::~Node(){
    // TODO
};
