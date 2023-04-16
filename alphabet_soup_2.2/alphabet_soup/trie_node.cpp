/**
 * @file trie_node.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <cassert>
#include <sstream>
#include <cstdint>

#include "trie_node.hpp"

TrieNode::TrieNode (bool is_key_state)
{
    //TODO
    is_key_ = is_key_state;
    iterator_ = children_.end();
    //
    assert(is_key()==is_key_state);
    assert(!current_exists());
};

TrieNode::Ref TrieNode::create(bool is_key_state)
{
    return std::make_shared<TrieNode>(is_key_state);
}

TrieNode::~TrieNode()
{}

bool TrieNode::is_key() const
{
    bool ret_val = true;
    //TODO
    ret_val = is_key_;
    //
    return ret_val;
}

bool
TrieNode::has(char k) const
{
    bool ret_v = false;
    //TODO
    if (children_.count(k)!= 0)
    {
        ret_v = true;
    }
    //
    return ret_v;
}

TrieNode::Ref
TrieNode::child(char k) const
{
    assert(has(k));
    TrieNode::Ref node = nullptr;
    //TODO
    node = children_.at(k);
    //
    return node;
}

bool
TrieNode::current_exists() const
{
    bool ret_val = true;
    //TODO
    if(iterator_ == children_.end())
    {
        ret_val = false;
    }
    //
    return ret_val;
}

TrieNode::Ref
TrieNode::current_node() const
{
    assert(current_exists());
    TrieNode::Ref node = nullptr;
    //TODO
    node = iterator_->second;
    //
    return node;
}

char
TrieNode::current_symbol() const
{
    assert(current_exists());
    char symbol = 0;
    //TODO
    if(current_exists())
    {
        symbol = iterator_->first;
    }
    //
    return symbol;
}

void
TrieNode::set_is_key_state(bool new_state)
{
    //TODO
    is_key_ = new_state;
    //
    assert(is_key()==new_state);
}

bool
TrieNode::find_child(char s)
{
    bool found = false;
    //TODO
    if(has(s) == true)
    {
        iterator_ = children_.find(s);
        found = true;
    }
    else
    {
        iterator_ = children_.end();
    }
    //
    assert(found || !current_exists());
    assert(!found || current_symbol()==s);
    return found;
}

void
TrieNode::goto_first_child()
{
    //TODO
    if(!children_.empty())
    {
        iterator_ = children_.begin();
    }
    else
    {
        iterator_ = children_.end();
    }
    //
}

void
TrieNode::goto_next_child()
{
    assert(current_exists());
    //TODO
    ++iterator_;
    //
}

void
TrieNode::set_child(char k, Ref node)
{
    assert(node != nullptr);
    //TODO
    children_[k] = node;
    iterator_ = children_.find(k);
    //
    assert(current_symbol()==k);
    assert(current_node()==node);
}

std::ostream&
TrieNode::fold(std::ostream& out) const
{
    //TODO
    //Hint: review c++ input/output manipulators at
    //      https://en.cppreference.com/w/cpp/io/manip
    out << "[";
    if(is_key()){
        out << "T";
    }else{
        out<<"F";
    }
    for(auto const& child : children_) {
        out << " " << std::hex << + child.first << " ";
        child.second->fold(out<< " ");
    }
    out << "]";
    //
    return out;
}

TrieNode::Ref TrieNode::create(std::istream& in) noexcept(false)
{
    TrieNode::Ref node = nullptr;
    //TODO
    std::string line;
    std::getline(in, line);
    if(line.empty() || line[0] != '[' || line.back() != ']')
    {
        throw std:: runtime_error("Wrong input format");
    }

    bool is_key_state = false;
    if (line[1] == 'T')
    {
        is_key_state = true;
    }

    node = std::make_shared<TrieNode>(is_key_state);
    std::istringstream iss (line.substr(2,line.size() - 3));
    char symbol;
    while (iss >> std::skipws >> symbol)
    {
        iss.ignore();
        TrieNode::Ref child_node = TrieNode::create(iss);
        node->set_child(symbol,child_node);
    }
    //
    return node;
}
