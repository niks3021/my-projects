class queue:
    def __init__ (Self):
        Self.Values = []
    def Enqueue(Self,x):
        Self.Values.append(x)
    def Dequeue(Self):
        Front = Self.Values[0]
        Self.Values = Self.Values[1:]
        return Front
q = queue()
q.Enqueue(10)
q.Enqueue(20)
q.Enqueue(30)
q.Enqueue(40)
print(q.Values)
q.Enqueue(50)
print(q.Values)
print(q.Dequeue())
print(q.Values)
    