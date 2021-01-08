import sys
import numpy as np

def play_yuts(step, prob_head=0.5):
  yuts = np.random.binomial(n=1, p=prob_head, size=4*step)
  print yuts
  play_list = np.sum(yuts.reshape([4, step]), axis=0)
  print play_list
  
  step = float(step)
  do = np.sum(play_list==0) / step
  gae = np.sum(play_list==1) / step
  geol = np.sum(play_list==2) / step
  yut = np.sum(play_list==3) / step
  mo = np.sum(play_list==4) / step

  print 'prob_head: %f' % prob_head
  print 'Probability mo: %f, %f' %(do, (1-prob_head)**4) + \
        '\nProbability do: %f, %f' %(gae, 4*(prob_head)*(1-prob_head)**3) + \
        '\nProbability gae: %f, %f' %(geol, 6*(prob_head**2)*((1-prob_head)**2)) + \
        '\nProbability geol: %f, %f' %(yut, 4*(prob_head**3)*(1-prob_head)) + \
        '\nProbability yut: %f, %f' %(mo, prob_head**4)
 
def main():
  if len(sys.argv) != 2:
    print 'usage: ./yut.py step'
    sys.exit(1)

  step = int(sys.argv[1])

  play_yuts(step)
  print ("")
  play_yuts(step, prob_head=0.3)

if __name__ == '__main__':
  main() 
