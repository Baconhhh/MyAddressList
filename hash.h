#ifndef HASH_H_
#define HASH_H_

#include <iostream>
#include <string>
#include <cstring>

using namespace std;
typedef long long  d_long;

class AddressList {
                private:
        string Name;
        long long Stu_ID;
        string College;
        long long Tel;
                public:
        // constructors and other methods
        AddressList ( const string name, const long long stu_id, const string college,
                      const long long tel );
        AddressList ();
        ~AddressList ();
        void show_list();
	string& nm(  )
	{
		return Name;
	}

        // overloaded operator friends
        friend std::ostream &operator<< ( ostream &os, AddressList &al );
//	friend std::istream &operator>>( istream &is,AddressList &al );
};

AddressList::AddressList ( const string name, const long long stu_id, const string college,
                           const long long tel ) {
	Name=name;
	College=college;
        Stu_ID = stu_id;
        Tel = tel;
}

AddressList::AddressList () {
	Name="nobody";
	College="None";
        Stu_ID = 0;
        Tel = 0;
}
AddressList::~AddressList () {
}
ostream &operator<<( ostream &os,AddressList &al )
{
	os<<"姓名:"<<al.Name<<'\n';
	os<<"学号:"<<al.Stu_ID<<'\n';
	os<<"学院:"<<al.College<<'\n';
	os<<"电话:" <<al.Tel<<'\n';

	return os;
}

template<class Key,class AddressList>
class HashNode
{
	public:
	       AddressList _addr; 
		Key _key=_addr.nm();
		HashNode *next;
	HashNode( Key key,AddressList addr)
	{
		_key=key;
		_addr=addr;
		next=NULL;
	}

	~HashNode() {}

	HashNode &operator=( const HashNode &node )
	{
		_key=node.key;
		_addr=node.addr;    
		
		next=node.next;
		return *this;
	}

	
};
template<class Key,class AddressList,class HashFunc,class EqualKey>
class HashMap
{
	public:
		HashMap( int size );
		~HashMap();
		bool insert( const Key &key,const AddressList&addr);
		bool del( const Key&key );
		AddressList&find( const Key &key );
		AddressList&operator[] ( const Key &key );
		void print() ;
	private:
		HashFunc hash;
		EqualKey equal;
		HashNode<Key, AddressList> **table;
		unsigned int _size;
		AddressList addrNULL;
};


template<class Key,class AddressList,class HashFunc,class EqualKey>
HashMap<Key, AddressList, HashFunc, EqualKey>::HashMap(int size):_size(size)
{
	hash=HashFunc();
	equal=EqualKey();
	table=new HashNode<Key, AddressList>*[_size];
	for( unsigned i=0;i<_size;i++ )
		table[i]=NULL;
}


template<class Key,class AddressList,class HashFunc,class EqualKey>
void HashMap<Key, AddressList, HashFunc, EqualKey>::print()
{

	for( unsigned i=0;i<_size;i++ )
	{
		HashNode<Key, AddressList>*currentNode=table[i];
		while( currentNode )
		{
			cout<<"------------------\n";
			cout<<currentNode->_addr;
			currentNode=currentNode->next;
	
		}
	}

}
template<class Key,class AddressList,class HashFunc,class EqualKey>
HashMap<Key, AddressList, HashFunc, EqualKey>::~HashMap()
{
	for( unsigned i=0;i<_size;i++ )
	{
		HashNode<Key, AddressList>*currentNode=table[i];
		while( currentNode )
		{
			HashNode<Key, AddressList>* temp=currentNode;
			currentNode=currentNode->next;
			delete temp;
		}
	}

	delete [] table;
}

template <class Key, class AddressList, class HashFunc, class EqualKey>
bool HashMap<Key, AddressList, HashFunc, EqualKey>::insert(const Key& key, const AddressList& addr)
{
    int index = hash(key)%_size;
    HashNode<Key, AddressList> * node = new HashNode<Key, AddressList>(key,addr);
    node->next = table[index];
    table[index] = node;
    return true;
}


template <class Key, class AddressList, class HashFunc, class EqualKey>
bool HashMap<Key, AddressList, HashFunc, EqualKey>::del(const Key& key)
{
    unsigned index = hash(key) % _size;
    HashNode<Key, AddressList> * node = table[index];
    HashNode<Key, AddressList> * prev = NULL;
    while (node)
    {
        if (node->_key == key)
        {
            if (prev == NULL)
            {
                table[index] = node->next;
            }
            else
            {
                prev->next = node->next;
            }
            delete node;
            return true;
        }
        prev = node;
        node = node->next;
    }
    return false;
}

template <class Key, class AddressList, class HashFunc, class EqualKey>
AddressList & HashMap<Key, AddressList, HashFunc, EqualKey>::find(const Key& key)
{
    unsigned  index = hash(key) % _size;
    if (table[index] == NULL)
        return addrNULL;
    else
    {
        HashNode<Key, AddressList> * node = table[index];
        while (node)
        {
            if (node->_key == key)
                return node->_addr;
            node = node->next;
        }
    }
}


template <class Key, class AddressList, class HashFunc, class EqualKey>
AddressList& HashMap<Key, AddressList, HashFunc, EqualKey>::operator [](const Key& key)
{
    return find(key);
}

class HashFunc
{
public:
    int operator()(const string & key )
    {
        int hash = 0;
        for(int i = 0; i < key.length(); ++i)
        {
            hash = hash << 7 ^ key[i];
        }
        return (hash & 0x7FFFFFFF);
    }
};


class EqualKey
{
public:
    bool operator()(const string & A, const string & B)
    {
        if (A.compare(B) == 0)
            return true;
        else
            return false;
    }
};

#endif
