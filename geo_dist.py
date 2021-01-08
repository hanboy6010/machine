import numpy as np
import sys
import matplotlib.pyplot as plt
import math

def geometric_experiment(boy_prob, step):
    girl_prob = 1.0 - boy_prob
    random_var_girl = np.random.geometric(p=girl_prob, size=step)
    max_num = np.max(random_var_girl)
   
    exp_x = 0
    exp_x2 = 0
    x_bin = []
    for i in range(1, max_num + 1):
        i_sum = (random_var_girl==i).sum()
        x_bin.append(i_sum)
        prob = i_sum /float(step)
        exp_x += i * prob
        exp_x2 += math.pow(i, 2) * prob
    print 'Mean: %.4f, %.4f' % (exp_x, 1/girl_prob)
    print 'Variance: %.4f, %.4f' % (exp_x2 - math.pow(exp_x, 2), (1.0 - girl_prob) / math.pow(girl_prob,2))

    x = 2 * np.arange(1, max_num + 1) - 1
    y = x_bin

    x2 = 2 * np.arange(1, max_num + 1)
    y2 = []
    for i in range(1, max_num + 1):
        y2.append(int((1.0-girl_prob)**(i-1) * girl_prob * step))
   
    plt.bar(x, y, align = 'center')
    plt.bar(x2, y2, color = 'g', align = 'center')
    plt.title('geo graph')
    plt.ylabel('Y axis')
    plt.xlabel('X axis')
    plt.show()

def main():
    if len(sys.argv) != 3:
        print 'usage: ./geo.py boy_prob step'
        sys.exit(1)

    boy_prob = float(sys.argv[1])
    step = int(sys.argv[2])

    geometric_experiment(boy_prob=boy_prob, step=step)

if __name__ == '__main__':
    main() 