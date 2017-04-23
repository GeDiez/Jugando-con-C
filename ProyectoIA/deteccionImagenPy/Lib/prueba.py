import Matriz as matriz


m = [[1,2,3],[4,5,6],[7,8,9]]

def f(item):
  return item * 2

def imprime(item):
  print item

m2 = matriz.map(f, m)