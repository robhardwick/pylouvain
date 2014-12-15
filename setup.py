from distutils.core import setup
from distutils.extension import Extension

setup(
    name = 'pylouvain',
    version = '0.0.1',
    description = 'Python wrapper for louvain/lambiotte classes',

    url = 'https://github.com/robhardwick/pylouvain',

    author = 'Rob Hardwick',
    author_email = 'robhardwick@gmail.com',

    license = 'MIT',

    classifiers = [
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 2',
        'Programming Language :: Python :: 2.7',
    ],

    ext_modules = [
        Extension(
            'pylouvain',
            ['src/pylouvain.cpp', 'src/graph.cpp'],
            include_dirs = ['include', '/usr/local/include'],
            library_dirs = ['/usr/local/lib'],
            libraries = ['boost_python-mt']
        ),
    ]
)
