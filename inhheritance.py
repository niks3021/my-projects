class OTTsubscription:
    def __init__(self ,subscription_id,plan,total_payment ):
        self.id = subscription_id
        self.plan = plan
        self.total_payment = total_payment
    def subscribe(self):
        print(f"subscriber with subscription id {self.id} has subscribed to the {self.plan} plan")
    def unsubscribe(self):
        print(f"subscriber with subscriber id {self.id} has unsubscribed to the {self.plan} plan")
class PremiumSubscription(OTTsubscription):
    def max_screens(self):
       x = input('set max screens to ; ')
       print('max screens set to ', x)
netflix = PremiumSubscription("121212", "monthly",5000)
netflix.subscribe()
netflix.max_screens()
        
        


        



