import os
from unittest import TestCase
from tempfile import mkdtemp
from shutil import rmtree

from pylouvain import Graph


class GraphTest(TestCase):

    def setUp(self):
        """ Prepare temporary directory for test runs """
        self.tmp_dir = mkdtemp()
        self.tmp = os.path.join(self.tmp_dir, 'test')

    def tearDown(self):
        """ Clean up after test runs """
        rmtree(self.tmp_dir)

    def test_init(self):
        """ Test graph initialisation """
        g = Graph()

    def test_add_edge(self):
        """ Test adding a graph edge """
        g = Graph()
        g.addEdge(1, 2, 0.1)

    def test_write_non_existent(self):
        """ Test writing a graph to a non-existent path """
        path = os.path.join(self.tmp, 'invalid', 'path')
        g = Graph()
        self.assertRaises(RuntimeError, g.write, path)

    def test_write_empty(self):
        """ Test writing an empty graph to disk """
        g = Graph()
        g.write(self.tmp)

        for ext, size in (('.bin', 4), ('.weights', 0)):
            path = self.tmp + ext
            assert os.path.isfile(path)

            info = os.stat(path)
            assert info.st_size == size

    def test_write(self):
        """ Test writing a graph to disk """
        g = Graph()
        g.addEdge(10, 20, 0.5)
        g.addEdge(10, 30, 0.1)
        g.addEdge(20, 30, 0.9)
        g.write(self.tmp)

        for ext, size in (('.bin', 276), ('.weights', 24)):
            path = self.tmp + ext
            assert os.path.isfile(path)

            info = os.stat(path)
            assert info.st_size == size
