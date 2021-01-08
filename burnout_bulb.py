import numpy as np
import sys

def expectation_burn_out(bulb_probs, burnout_prob, step):
  # experiments
  bulb_type = range(len(bulb_probs))
  select_bulb = np.random.choice(bulb_type, p=bulb_probs, size=step)
  steps = []
  for bulb_num in bulb_type:
    steps.append((select_bulb == bulb_num).sum())
  
  bulb_vars = []
  for bulb_num in bulb_type: 
    bulb_vars.append(np.random.geometric(p=burnout_prob[bulb_num], size=steps[bulb_num]))
  bulb_vars = np.concatenate(bulb_vars)
  
  # true probability
  true_prob = 0
  for bulb_num in bulb_type:
    true_prob += bulb_probs[bulb_num] * 1.0 / burnout_prob[bulb_num]

  # print
  print np.mean(bulb_vars), true_prob

def main():
  argc = len(sys.argv)
  if not(argc >= 6 and argc % 2 == 0):
    print 'usage: ./total_exp.py step A_prob A_burnout_probs B_prob B_burnout_probs ...'
    sys.exit(1)
  step = int(sys.argv[1])

  num_type = (argc - 2) // 2
  bulb_probs = []
  burnout_prob = []
  for i in [2 * n + 2 for n in range(num_type)]:
    bulb_probs.append(float(sys.argv[i]))
    burnout_prob.append(float(sys.argv[i+1]))

  assert np.abs(np.sum(bulb_probs) - 1.0) < np.finfo(float).eps, 'total probability should be 1'

  expectation_burn_out(bulb_probs=bulb_probs, burnout_prob=burnout_prob, step=step)

if __name__ == '__main__':
  main() 