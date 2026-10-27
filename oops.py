class faculty:
    def __init__ (self,a,b,c):
        self.id = a
        self.name = b
        self.salary = c
    def display(self):
        print('faculty id ', self.id)
        print('name', self.name)
        print('salary', self.salary)
class clubs(faculty):
    def __init__ (self,a,b,c,d):
        super().__init__(self,a,b,c)
a = faculty(69,"nikhil",27000)
a.display()
def count_up_to(n):
    count = 0
    while count < n:
        yield count
        count += 1

# Using the generator
for number in count_up_to(5):
    print(number)




        
