#pragma once
#include"SafeArray.h"
#include<iomanip>

template<class t>
class Graph{
public:
	Graph<t>();
	~Graph<t>();
	void addVertex(t& v);
	void print();	
	void setEdge(t& from, t& to, int weight);
	void nextHopPrint();
	int size();
	bool isEmpty();
	bool getEdge(const t& fromVertex, const t& toVertex);
	int getEdgeWeight(const t& fromVertex, const t& toVertex);
	SafeArray<t> getIncomingNeighbors(const t& vertex);
	SafeArray<t> getOutgoingNeighbors(const t& vertex);
	void printRoutingTable();
	void topSort();

private:
	SafeArray<t> vertices;
	int num_elements;
	int** adj_matrix;
	int** next_hop;
	void resizeMatrix();
	int special;
	void createNextHop();
	int** weight_table;
};

template<class t>
Graph<t>::Graph():vertices(1){
	num_elements = 0;
	special = 2;	
}

template<class t>
Graph<t>::~Graph(){
	delete [] adj_matrix;
	delete [] next_hop;
	delete [] weight_table;
}

template<class t>
void Graph<t>::addVertex(t& v){
	if(num_elements == 0){
		vertices[0] = v;
		adj_matrix = new int *[1];
		adj_matrix[0] = new int[1];
		adj_matrix[0][0] = 0;		
	}
	else{
		vertices.push_back(v);
		resizeMatrix();
	}
	num_elements++;
}

template<class t>
void Graph<t>::print(){
	
	for(int i = 0; i < num_elements; i++){
		cout<<"************************"<<endl;
		cout<<vertices[i]<<":"<<endl;
		cout<<"Incoming neighbors:"<<endl;		

		SafeArray<string> elem(getIncomingNeighbors(vertices[i]));	
		for(int j = 0; j < elem.size(); j++)
			cout<<setw(8)<<""<<elem[j]<<endl;		

		cout<<endl;

		cout<<"Outgoing Neighbors:"<<endl;
			
		SafeArray<string> elem1(getOutgoingNeighbors(vertices[i]));
		for(int j = 0; j < elem1.size(); j++)
			cout<<setw(8)<<""<<elem1[j]<<endl;

		cout<<endl;	
		cout<<"************************"<<endl<<endl<<endl;
	}
}

template<class t>
void Graph<t>::resizeMatrix(){
	
	int **temp_array;
	temp_array = new int *[num_elements+1];
	for(int i = 0; i<num_elements+1; i++)
		temp_array[i] = new int[num_elements+1];

	for(int i = 0; i < num_elements+1; i++){
		for(int j = 0; j < num_elements+1; j++){			
			if( i == j )
				temp_array[i][j] = 0;
			else if(i == num_elements || j == num_elements)
				temp_array[i][j] = special;
			else
				temp_array[i][j] = adj_matrix[i][j];
		}
	}

	for(int i = 0; i < num_elements; i++)
		delete [] adj_matrix[i];					

	adj_matrix = temp_array;
	
}

template<class t>
void Graph<t>::setEdge(t& from, t& to, int weight){
	int to_index;
	int from_index;

	for(int i = 0; i <vertices.size(); i++){
		if(from == vertices[i])
			from_index = i;
		if(to == vertices[i])
			to_index = i;
	}

	adj_matrix[from_index][to_index] = weight;
	
	
}

template<class t>
void Graph<t>::nextHopPrint(){
	for(int i = 0 ; i <num_elements; i ++){
		for(int j = 0; j < num_elements; j++){
			cout<<setw(4)<<adj_matrix[i][j]<<"   ";
		}
		cout<<endl;
	}
}

template<class t>
int Graph<t>::size(){
	return num_elements;
}

template<class t>
bool Graph<t>::isEmpty(){
	if(num_elements == 0)
		return true;
	else
		return false;
}

template<class t>
bool Graph<t>::getEdge(const t& fromVertex, const t& toVertex){
	int from_index;
	int to_index;

	for(int i = 0; i < vertices.size(); i++){
		if(vertices[i] == fromVertex)
			from_index = i;
		if(vertices[i] == toVertex)
			to_index = i;
	}

	if(adj_matrix[from_index][to_index] == 0)
		return false;
	else
		return true;
}

template<class t>
int Graph<t>::getEdgeWeight(const t& fromVertex, const t& toVertex){
	int from_index;
	int to_index;

	for(int i = 0; i < vertices.size(); i++){
		if(vertices[i] == fromVertex)
			from_index = i;
		if(vertices[i] == toVertex)
			to_index = i;
	}

	return adj_matrix[from_index][to_index];
}

template<class t>
SafeArray<t> Graph<t>::getIncomingNeighbors(const t& vertex){
	SafeArray<t> inc_neighbors(1);
	int inc_size = 0;
	
	int vert_index;
	for(int i = 0; i < vertices.size(); i++){
		if(vertex == vertices[i])
			vert_index = i;
	}			

	for(int i = 0; i < num_elements; i++){
		if(adj_matrix[i][vert_index] != 0 && adj_matrix[i][vert_index] != special){
			if(inc_size == 0)
				inc_neighbors[0] = vertices[i];
			else
				inc_neighbors.push_back(vertices[i]);
			inc_size++;
		}
	}	
	
	return inc_neighbors;
}

template<class t>
SafeArray<t> Graph<t>::getOutgoingNeighbors(const t& vertex){
	SafeArray<t> out_neighbors(1);
	int out_size = 0;

	int vert_index;
	for(int i = 0; i < vertices.size(); i++){
		if(vertex == vertices[i])
			vert_index = i;
	}			

	for(int i = 0; i < num_elements; i++){
		if(adj_matrix[vert_index][i] != 0 && adj_matrix[vert_index][i] != special){
			if(out_size == 0)
				out_neighbors[0] = vertices[i];
			else
				out_neighbors.push_back(vertices[i]);
			out_size++;
		}
	}	

	return out_neighbors;
}

template<class t>
void Graph<t>::topSort(){
	int *arr = new int[num_elements];
	string *arr2 = new string[num_elements];

	int counter = 0;
	for(int i = 0; i < num_elements; i++){
		for(int j = 0; j < num_elements; j++){
			if(adj_matrix[i][j] != special && adj_matrix[i][j] != 0)
				counter++;
		}
		arr[i] = counter;
		arr2[i] = vertices[i];		
		counter = 0;
	}

	bool swapped = true;
	int j = 0; 
	while(swapped){
		swapped = false;
		j++;
		for(int i = 0; i < num_elements - j; i++){
			if(arr[i] < arr[i+1]){				
				swap(arr[i],arr[i+1]);
				swap(arr2[i], arr2[i+1]);
				swapped = true;
			}
		}
	}
	cout<<"Finding a path through the graph:"<<endl;
	for(int i = 0; i <num_elements; i++)		
		cout<<setw(8)<<""<<arr2[i]<<endl;
}

template<class t>
void Graph<t>::printRoutingTable(){
	createNextHop();
	for(int i = 0; i < num_elements; i++){
		cout<<vertices[i]<<" to:"<<endl;
		for(int j = 0; j < num_elements; j++){
			if(next_hop[i][j] != 0)
				cout<<setw(8)<<""<<vertices[j]<<" Total weight: "<<weight_table[i][j]<<" Next Hop: "<<vertices[next_hop[i][j]]<<endl;
		}
		cout<<endl;
	}
}

template<class t>
void Graph<t>::createNextHop(){
	next_hop = new int*[num_elements];	
	weight_table = new int*[num_elements];
	for(int i = 0; i < num_elements; i++){
		weight_table[i] = new int[num_elements];
		next_hop[i] = new int[num_elements];
	}

	for(int i = 0; i <num_elements; i++){
		for(int j = 0; j < num_elements; j++){
			weight_table[i][j] = 0;
			next_hop[i][j] = 0;
		}
	}
	

	for(int common = 0; common < vertices.size(); common++){						
		for(int i = 0; i < vertices.size(); i++){
			if(adj_matrix[i][common] != special ){
				for(int j = 0; j <vertices.size(); j++){
					if(adj_matrix[common][j] != special ){
						if( i != j) {
							int weight = adj_matrix[i][common] + adj_matrix[common][j];						
							if(weight_table[i][j] == 0){
								weight_table[i][j] = weight;
								next_hop[i][j] = common;}
							else if(weight_table[i][j] > weight){
								weight_table[i][j] = weight;
								next_hop[i][j] = common;
							}
						}
						
					}						
				}
			}
		}
	}	
}

