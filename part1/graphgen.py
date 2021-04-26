
import numpy as np
import matplotlib.pyplot as plt
import statistics as st

f1_4_total = 3254449
f1_4 = [816782, 812642, 808060, 816965]
f1_128_total = 378
f1_128 = [6, 6, 8, 4, 5, 4, 6, 3, 6, 8, 4, 4, 4, 4, 3, 4, 4, 4, 4, 3, 4, 3, 3,
3, 3, 4, 4, 3, 2, 2, 3, 2, 2, 3, 3, 3, 2, 2, 3, 3, 3, 3, 3, 3, 3, 2,
3, 3, 2, 2, 2, 4, 3, 2, 2, 2, 4, 3, 3, 3, 3, 3, 3, 3, 3, 2, 3, 3, 2,
2, 3, 2, 2, 3, 3, 3, 2, 3, 3, 3, 3, 2, 3, 3, 3, 3, 3, 2, 3, 2, 3, 2,
3, 3, 2, 3, 2, 3, 2, 2, 2, 2, 3, 3, 2, 3, 2, 2, 3, 3, 2, 3, 4, 2, 2,
2, 2, 2, 2, 3, 2, 2, 3, 2, 2, 2, 2, 2]


b1_4_total = 3913745
b1_4 = [979333, 979133, 976631, 978648]
b1_128_total = 838
b1_128 = [101, 100, 94, 93, 90, 89, 88, 1, 1, 35, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 1, 2, 2, 1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]


# with yield on spin loops
b2_4_total = 1770918
b2_4 =[442842, 442809, 442844, 442423]
b2_128_total =47294
b2_128 = [211, 210, 209, 207, 205, 203, 203, 21382, 195, 192, 195, 193, 193, 192, 191, 192, 191, 191, 191, 191, 191, 191, 191, 191, 194, 191, 191, 191, 192, 191, 191, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 193, 192, 192, 195, 426, 204, 196, 192, 192, 192, 191, 192, 191, 192, 191, 192, 192, 192, 192, 193, 192, 192, 192, 196, 197, 192, 192, 192, 192, 192, 207, 208, 192, 193, 194, 192, 195, 195, 229, 235, 196, 195, 196, 192, 272, 281, 192, 199, 199, 199, 199, 202, 192, 400, 425, 203, 438, 205, 192, 192, 214, 216, 218, 214, 216, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192]

f2_4_total = 1916612
f2_4 = [476608, 481673, 477015, 481316]
f2_128_total = 9496
f2_128 = [71, 77, 77, 69, 71, 76, 76, 469, 89, 68, 68, 68, 69, 69, 69, 69, 68, 74, 74, 75, 73, 74, 75, 75, 75, 74, 74, 75, 74, 73, 75, 75, 75, 75, 74, 74, 74, 75, 75, 75, 75, 75, 73, 75, 74, 74, 75, 73, 73, 74, 74, 75, 75, 75, 75, 74, 75, 69, 69, 69, 69, 67, 68, 68, 68, 67, 69, 68, 69, 70, 68, 70, 69, 68, 68, 69, 70, 67, 69, 68, 70, 70, 69, 68, 68, 70, 69, 68, 68, 70, 69, 68, 68, 69, 69, 68, 70, 68, 70, 68, 70, 68, 68, 69, 69, 68, 68, 68, 70, 70, 68, 68, 69, 69, 67, 66, 68, 69, 70, 68, 69, 69, 68, 68, 75, 75, 75, 75]


x_axis1 = np.linspace(1,4, 4)
x_axis2 = np.linspace(1,4, 128)
print(x_axis1)
# plt.title("4 threads on 4-core machine, without thread_yield()")
# plt.title("128 threads on 4-core machine, without thread_yield()")
# plt.title("4 threads on 4-core machine, with thread_yield()")
plt.title("128 threads on 4-core machine, with thread_yield()")
# plt.plot(x_axis1, sorted(b1_4, reverse=True), color='darkblue', marker='x', label="Bakery ("+str(b1_4_total)+" total calls)")
# plt.plot(x_axis1, sorted(f1_4, reverse=True), color='darkred', marker='x', label="Filter ("+str(f1_4_total)+" total calls)")
# plt.plot(x_axis2, sorted(b1_128, reverse=True), color='darkblue', marker='', label="Bakery ("+str(b1_128_total)+" total calls)")
# plt.plot(x_axis2, sorted(f1_128, reverse=True), color='darkred', marker='', label="Filter ("+ str(f1_128_total)+" total calls)")
# plt.plot(x_axis2, sorted(b2_128, reverse=True), color='darkblue', marker='', label="Bakery ("+str(b2_128_total)+" total calls)")
# plt.plot(x_axis2, sorted(f2_128, reverse=True), color='darkred', marker='', label="Filter ("+ str(f2_128_total)+" total calls)")

plt.plot(x_axis2, sorted(b2_128, reverse=True), color='darkblue', marker='', label="Bakery ("+str(b2_128_total)+" total calls)")
plt.plot(x_axis2, sorted(f2_128, reverse=True), color='darkred', marker='', label="Filter ("+ str(f2_128_total)+" total calls)")
plt.xlabel("Mutex #")
plt.ylabel("Call count")
plt.grid(True)
plt.legend()
plt.show()


print(st.stdev(b1_128))
print(st.stdev(f1_128))






