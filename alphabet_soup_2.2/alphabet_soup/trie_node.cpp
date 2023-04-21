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
    // Escribe el estado de este nodo en el flujo de salida.
    out << "[";
    if (is_key()) {
        out << " T";
    } else {
        out << " F";
    }
    if (!children_.empty()) {
        for (auto const& child : children_) {
            out << " " << std::hex << +child.first;
            child.second->fold(out << " ");
        }
    }
    out << " ]";
    //
    return out;
}

TrieNode::Ref TrieNode::create(std::istream& in) noexcept(false)
{
    TrieNode::Ref node = nullptr;
    //TODO
    char c;
     in >> c;
     if (c != '[') {
         throw std::runtime_error("Wrong input format");
     }

     node = std::make_shared<TrieNode>();

     bool is_key = false; // siempre establecer is_key como false
     in >> c;
     if (c == 'T') {
         is_key = true;
     } else if (c != 'F') { // establecer is_key como false si la marca no es 'F'
         throw std::runtime_error("Wrong input format");
     }

     while (in >> c) {
         if (c == ']') {
             break;
         } else if (c == ' ') {
             continue;
         } else {
             in.putback(c);
             char hex[3];
             in.read(hex, 2);
             hex[2] = '\0';
             unsigned char symbol = static_cast<unsigned char>(std::strtol(hex, nullptr, 16));
             node->children_.emplace(symbol, TrieNode::create(in));
         }
     }

     node->is_key_ = is_key;
     if (c != ']') {
         throw std::runtime_error("Wrong input format");
     }
    //
    return node;
}
