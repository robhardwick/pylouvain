#ifndef PYLOUVAIN_HPP
#define PYLOUVAIN_HPP

#include <string>
#include <vector>

namespace pylouvain {

    typedef std::vector<std::vector<std::pair<int, float> > > links_t;
    typedef links_t::size_type links_size_t;

    class Graph {
        public:
            Graph() {}
            void addEdge(unsigned int src, unsigned int dest, double weight);
            void write(const std::string &basename);

        private:
            links_t links;
    };

}

#endif
