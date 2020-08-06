#include <string>

class Node{
    private:
        /* data */
    public:
        int data;

        Node(int data_in);
        ~Node();
};

Node::Node(int data_in){
    data = data_in;
}

Node::~Node(){

}


int main(){
    Node node = Node(12);
    printf("Node: %d\n",node.data);
}