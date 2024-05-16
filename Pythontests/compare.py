for i in range(1,4):
    txt = f"ply{i}.txt"
    csv = f"ply{i}.csv"
    file = open(txt, "r")
    text1 = file.read()
    file.close()
    file = open(csv, "r")
    text2 = file.read()
    file.close()
    testlist1 = text1.split("\n")
    testlist2 = text2.split("\n")
    count = 0
    found = []
    for value in testlist2:
        if not value in testlist1:
            print(value)
            if not value in found:
                found.append(value)
            count += 1
    print("NON-UNIQUE COUNT: " + str(count))
    print("UNIQUE COUNT: " + str(len(found)))
    for value in found:
        print(value)
    print("\n\n\n")