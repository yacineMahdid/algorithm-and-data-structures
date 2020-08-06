#include <string>

class Node{
    private:
        /* data */
    public:
        int data; // this could be anything
        Node* next; // pointer to the next node

        Node(int data_in);
        Node();

        ~Node();
};

// Constructors
Node::Node(){
    
}

Node::Node(int data_in){
    data = data_in;
}

// Destructor
Node::~Node(){

}

class CircularLinkedList{
    private:
        /* data */
    public:
        Node *head;
        Node *tail;
        int length;

        CircularLinkedList();
        ~CircularLinkedList();

        void insert_node(Node* node, int index);
        void delete_node(int index);
        void display();
};

CircularLinkedList::CircularLinkedList(){
    head = NULL;
    tail = NULL;
    length = 0;
}

CircularLinkedList::~CircularLinkedList(){

}

void CircularLinkedList::insert_node(Node* node, int index){

    // Case where the index is bigger than the length of the list
    if (length < index){
        return;
    }

    // Case where the index is 0
    if (index == 0 && head == NULL){
        head = node;
        tail = node;
        node->next = node;
        length++;
        return;
    } else if (index == 0){
        node->next = head;
        head = node;
        tail->next = head;
        length++;
        return;
    }

    // Case where the index == length
    if (index == length){
        tail->next = node;
        node->next = head;
        tail = node;
        printf("Node: %d\n", tail->data);
        length++;
        return;
    }


    // Iterate through the linked list until we find the right prev_node and cur_node
    int cur_index = 0;
    Node *cur_node = head;
    Node *prev_node = head;

    while (cur_index != index){
        // Move to the right of the linked list
        cur_index++;
        prev_node = cur_node;
        cur_node = cur_node->next;
    }

    // At this point we have that cur_index == index
    prev_node->next = node;
    node->next = cur_node;
    length++;
    return;
}

void CircularLinkedList::delete_node(int index){

     // Case where the index is bigger or equal than the length of the list
    if (length <= index){
        return;
    }

    // Case where the index is 0
    if (index == 0 && length == 1){
        head = NULL;
        tail = NULL;
        length = 0;
        return;
    } else if (index == 0){
        head = head->next;
        tail->next = head;
        length--;
        return;
    }

    // Iterate through the linked list until we find the right prev_node and cur_node
    int cur_index = 0;
    Node *cur_node = head;
    Node *prev_node = head;

    while (cur_index != index){
        // Move to the right of the linked list
        cur_index++;
        prev_node = cur_node;
        cur_node = cur_node->next;
    }

    // Here we need to delete the last node
    if (cur_index == length - 1){
        tail = prev_node;
        tail->next = head;
        length--;
        return;
    }

    // At this point we have that cur_index == index and we want to delete a node in the middle
    prev_node->next = cur_node->next;
    length--;
    return;
}

void CircularLinkedList::display(){
    
    Node *cur_node = head;
    int cur_index = 0;
    while (length > cur_index){

        printf("Node #%d: %d\n",cur_index, cur_node->data);
        cur_node = cur_node->next;
        cur_index++;
    }
}


int main(){
    CircularLinkedList list = CircularLinkedList();


    printf("INSERT\n");
    Node node_1 = Node(12);
    list.insert_node(&node_1, 0);

    Node node_2 = Node(13);
    list.insert_node(&node_2, 0);
    
    Node node_3 = Node(14);
    list.insert_node(&node_3, 0);

    list.display();

    printf("DELETE:\n");

    list.delete_node(0);
    list.delete_node(0);

    list.display();
}