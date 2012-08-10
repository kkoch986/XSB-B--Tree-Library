yappl -g "['generator_yap.pl'], test1(100000), test2(100000),  test3(100000), test4(100000), halt."
swipl -g "['generator_swi.pl'], test1(100000), test2(100000),  test3(100000), test4(100000), halt."


yappl -g "['generator_yap.pl'], test1(1000000), test2(1000000),  test3(1000000), test4(1000000), halt."
doesn't work
