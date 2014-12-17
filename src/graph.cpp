#include <iostream>
#include <fstream>
#include <map>
#include <stdexcept>
#include <boost/exception/enable_current_exception.hpp>
#include "pylouvain.hpp"

#define RUNTIME_ERROR(msg) boost::enable_current_exception(std::runtime_error(msg));

using namespace pylouvain;

/**
 * Add a weighted edge to the graph
 */
void Graph::addEdge(unsigned int src, unsigned int dest, double weight) {
    // Resize if necessary
    links_size_t size = std::max(src, dest) + 1;
    if (links.size() <= size) {
        links.resize(size);
    }

    // Add src -> dest edge
    links[src].push_back(std::make_pair(dest, weight));

    // Add dest -> src edge
    if (src != dest) {
        links[dest].push_back(std::make_pair(src, weight));
    }
}

/**
 * Clean
 */
void Graph::clean() {
    for (unsigned int i = 0; i < links.size(); i++) {
        std::map<int, float> m;
        std::map<int, float>::iterator it;

        for (unsigned int j = 0; j < links[i].size(); j++) {
            it = m.find(links[i][j].first);
            if (it == m.end()) {
                m.insert(std::make_pair(links[i][j].first, links[i][j].second));
            } else {
                it->second+=links[i][j].second;
            }

            std::vector<std::pair<int, float> > v;
            for (it = m.begin(); it != m.end(); it++) {
                v.push_back(*it);
            }

            links[i].clear();
            links[i]=v;
        }
    }
}

/**
 * Serialise graph to disk
 */
void Graph::write(const std::string& basename) {
    // Build output file names
    std::string fnlinks = basename + ".bin",
                fnweights = basename + ".weights";

    // Open output files
    std::ofstream olinks(fnlinks.c_str(), std::fstream::out | std::fstream::binary),
                  oweights(fnweights.c_str(), std::fstream::out | std::fstream::binary);

    // Ensure output files are writable
    if (!olinks.good()) {
        throw RUNTIME_ERROR("Unable to open '" + fnlinks + "' for writing");
    } else if (!oweights.good()) {
        throw RUNTIME_ERROR("Unable to open '" + fnweights + "' for writing");
    }

    // Write number of links
    unsigned int size = (unsigned int)links.size();
    olinks.write((char *)(&size), sizeof(unsigned int));

    // Write cumulative degree sequence
    long total = 0;
    for (unsigned int i = 0; i < size; i++) {
        total += (long)links[i].size();
        olinks.write((char *)(&total), sizeof(long));
    }

    // Write links and weights
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < links[i].size(); j++) {

            // Write link
            int dest = links[i][j].first;
            olinks.write((char *)(&dest), sizeof(int));

            // Write weight
            float weight = links[i][j].second;
            oweights.write((char *)(&weight), sizeof(float));

        }
    }

    // Close output files
    olinks.close();
    oweights.close();
}
