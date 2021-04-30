
import math
import numpy as np
import matplotlib.pyplot as plt
import statistics as st


coarse = [509691 , 219912 , 932040 , 256487 , 70468 , 641021 , 138555 , 221786 , 779410 , 216370]
rw = [1179998 , 754236 , 845619 , 1011980 , 793589 , 882606 , 763324 , 1255303 , 751614,  1279019]
swaptop = [1080432,  697083 , 972741 , 777407 , 635376 , 514091 , 738756 , 1166031 , 672936 , 696771]

sd1 = (st.stdev(coarse))
sd2 = (st.stdev(rw))
sd3 = (st.stdev(swaptop))

print(str(sd1/398574))
print(str(sd2/951728))
print(str(sd3/795162))






