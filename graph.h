#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "pq.h"

class graph {
    struct Vertex {
        std::string label;
        char val;
        int cost;

        std::unordered_set<std::string> adj;

        Vertex(std::string label, char val, int cost)
            : label(label),
              val(val),
              cost(cost),
              adj(std::unordered_set<std::string>()) {}
        Vertex(std::string label)
            : label(label),
              val('\0'),
              cost(0),
              adj(std::unordered_set<std::string>()) {}

        Vertex()
            : label(""),
              val('\0'),
              cost(0),
              adj(std::unordered_set<std::string>()) {}

        void add(std::string l) { adj.insert(l); }

        void add(Vertex v) { adj.insert(v.label); }
    };

   private:
    using Map = std::unordered_map<std::string, Vertex>;
    Vertex begin;
    Vertex end;
    Map verts;

    bool cmp(const std::string l, const std::string r) {
        return verts.find(l)->second.cost > verts.find(r)->second.cost;
    }

   public:
    graph(std::vector<std::string> ops)
        : begin(Vertex("B")), end(Vertex("E")), verts(Map()) {
        end.cost = 1;
        verts.insert({begin.label, begin});
        verts.insert({end.label, end});

        for (auto word : ops) {
            std::string parent_label = begin.label;
            // std::cout << "word: " << word << std::endl;
            for (int i = 0; i < word.length(); i++) {
                char val = word[i];
                std::string label = val + std::to_string(i);
                // std::cout << "\t" << val;

                if (verts.find(label) == verts.end())
                    verts.insert({label, Vertex(label, val, 0)});
                Vertex& child = verts.find(label)->second;
                // std::cout << " -> " << child.label << std::endl;
                child.cost++;

                Vertex& parent = verts.find(parent_label)->second;
                if (i == 0)
                    begin.add(child.label);
                else
                    parent.add(child.label);

                parent_label = label;
            }
            verts[parent_label].add(end);
        }
    }

    void display_graph(std::ostream& o) {
        o << "BEGIN: ";
        for (auto c : begin.adj) {
            o << c << ", ";
        }
        o << std::endl;

        Vertex vtx;
        for (auto v : verts) {
            if (v.first == begin.label || v.first == end.label) continue;
            vtx = v.second;
            o << vtx.label << ", " << vtx.cost << ": ";
            for (auto adj : vtx.adj) {
                o << adj << ", ";
            }
            o << std::endl;
        }

        o << "END: ";
        for (auto c : end.adj) {
            o << c << ", ";
        }
        o << std::endl;
    }

    std::string dijkstra() {
        std::unordered_map<std::string, int> d;
        std::unordered_map<std::string, std::string> p;

        auto cmp = [&](const std::string l, const std::string r) {
            return d.find(l)->second > d.find(r)->second;
        };

        PQ<std::string, decltype(cmp)> pq(cmp);
        for (auto it : verts) {
            std::string label = it.first;
            pq.push(label);
            d.insert({label, INT16_MIN});
            p.insert({label, ""});
        }
        d[begin.label] = 1;

        auto relax = [&](const std::string u, const std::string v,
                         const int w) {
            int& u_d = d.find(u)->second;
            int& v_d = d.find(v)->second;
            if (v_d < u_d + w) {
                v_d = u_d + w;
                p[v] = u;
                return true;
            }
            return false;
        };

        while (!pq.empty()) {
            std::string max_label = pq.pop();
            // std::cout << max_label << std::endl;
            Vertex& max = max_label == begin.label
                              ? begin
                              : verts.find(max_label)->second;

            for (auto e : max.adj) {
                Vertex adj = verts.find(e)->second;
                bool r = relax(max_label, adj.label, adj.cost);
                if (r) pq.sorted = false;
            }
        }

        std::string prev = p[end.label];
        std::string key;
        while (prev != begin.label) {
            key += prev[0];
            prev = p[prev];
        }
        return key;
    }
};