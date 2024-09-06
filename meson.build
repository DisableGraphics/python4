project('python4', 'cpp', version : '0.0.1')

py4_sources = ['main.cpp']
ssl = dependency('openssl')

pip4_sources = ['pip4.cpp']

executable('python4', py4_sources, dependencies: [ssl])
executable('pip4', pip4_sources)