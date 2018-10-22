from matplotlib import pyplot as pl

import os

directory = './energies/'

files = os.listdir(directory)

count = 0
for item in files:
    files[count] = directory+item
    count += 1

data = {}
for item in files:
    name = item.split('/')[-1]
    data[name] = {'time': [], 'cohesive': [], 'kinetic': [], 'total': []}

    with open(item) as file:
        next(file)
        for line in file:
            values = line.strip().split(' ')
            values = [float(i) for i in values]
            data[name]['time'].append(values[0])
            data[name]['cohesive'].append(values[1])
            data[name]['kinetic'].append(values[2])
            data[name]['total'].append(values[3])

skip = 0 # The skip to ignore settling data
end = None
for key in data:
    pl.plot(data[key]['time'][skip:end], data[key]['cohesive'][skip:end], label='Potential')
    pl.plot(data[key]['time'][skip:end], data[key]['kinetic'][skip:end], label='Kinetic')
    pl.plot(data[key]['time'][skip:end], data[key]['total'][skip:end], label='Total')

    pl.xlabel('Time [s]')
    pl.ylabel('Energy [eV/atom]')
    pl.legend(loc='best')
    pl.grid()
    pl.savefig('./figures/'+key+'single')
    pl.show()
    pl.clf()

for key in data:
    name = key.split('p')[-1]
    name = '0.'+name+' [ps]'
    pl.plot(data[key]['time'][skip:], data[key]['total'][skip:], label=name)

pl.xlabel('Time [s]')
pl.ylabel('Energy [eV/atom]')
pl.legend(loc='best')
pl.grid()
pl.savefig('./figures/all')
pl.clf()