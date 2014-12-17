#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include "pylouvain.hpp"

using namespace boost::python;
using namespace pylouvain;

BOOST_PYTHON_MODULE(pylouvain) {

    // Graph class
    class_<Graph>("Graph", init<>())
        .def("addEdge", &Graph::addEdge)
        .def("clean", &Graph::clean)
        .def("write", &Graph::write);

}
