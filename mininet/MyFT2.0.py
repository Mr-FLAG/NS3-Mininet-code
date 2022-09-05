from mininet.topo import Topo

#Test 4 ary Fat-tree topo:
#
#         
#      c0        c1        c2        c3
#       
#
#   a0   a1   a2   a3   a4   a5   a6   a7 
#    |\ /|     |\ /|     |\ /|     |\ /|   
#    | X |     | X |     | X |     | X |
#    |/ \|     |/ \|     |/ \|     |/ \|
#   e0   e1   e2   e3   e4   e5   e6   e7
#    |   |     |   |     |   |     |   |
#   h0   h1   h2   h3   h4   h5   h6   h7

class MyTopo(Topo):

    def __init__(self):

        # Init Topo
        Topo.__init__(self)
	
	#Add nodes
	#hosts
        h0 = self.addHost('h0', ip='10.0.0.1')
        h1 = self.addHost('h1', ip='10.0.1.1')
        h2 = self.addHost('h2', ip='10.1.0.1')
        h3 = self.addHost('h3', ip='10.1.1.1')
        h4 = self.addHost('h4', ip='10.2.0.1')
        h5 = self.addHost('h5', ip='10.2.1.1')
        h6 = self.addHost('h6', ip='10.3.0.1')
        h7 = self.addHost('h7', ip='10.3.1.1')
        
        #core layer
        c0 = self.addSwitch('c0')
        c1 = self.addSwitch('c1')
        c2 = self.addSwitch('c2')
        c3 = self.addSwitch('c3')

	#aggregation layer
        a0 = self.addSwitch('a0')
        a1 = self.addSwitch('a1')
        a2 = self.addSwitch('a2')
        a3 = self.addSwitch('a3')
        a4 = self.addSwitch('a4')
        a5 = self.addSwitch('a5')
        a6 = self.addSwitch('a6')
        a7 = self.addSwitch('a7')
        
        #Edge layer / Access layer
        e0 = self.addSwitch('e0')
        e1 = self.addSwitch('e1')
        e2 = self.addSwitch('e2')
        e3 = self.addSwitch('e3')
        e4 = self.addSwitch('e4')        
        e5 = self.addSwitch('e5')
        e6 = self.addSwitch('e6')
        e7 = self.addSwitch('e7')
        
        #add links
        #hosts to Access layer
        self.addLink(h0, e0)
        self.addLink(h1, e1)
        self.addLink(h2, e2)
        self.addLink(h3, e3)
        self.addLink(h4, e4)
        self.addLink(h5, e5)
        self.addLink(h6, e6)
        self.addLink(h7, e7)
        
        #Aggregation layer to Access layer
        #Pod 1
        self.addLink(a0, e0)
        self.addLink(a0, e1)
        self.addLink(a1, e0)
        self.addLink(a1, e1)
        #Pod 2 
        self.addLink(a2, e2)
        self.addLink(a2, e3)
        self.addLink(a3, e2)
        self.addLink(a3, e3)
        #Pod 3 
        self.addLink(a4, e4)
        self.addLink(a4, e5)
        self.addLink(a5, e4)
        self.addLink(a5, e5)
        #Pod 4 
        self.addLink(a6, e6)
        self.addLink(a6, e7)
        self.addLink(a7, e6)
        self.addLink(a7, e7)
        
        #Core layer to Aggregation layer
        self.addLink(c0, a0)
        self.addLink(c0, a2)
        self.addLink(c0, a4)
        self.addLink(c0, a6)
        
        self.addLink(c1, a0)
        self.addLink(c1, a2)
        self.addLink(c1, a4)
        self.addLink(c1, a6)
        
        self.addLink(c2, a1)
        self.addLink(c2, a3)
        self.addLink(c2, a5)
        self.addLink(c2, a7)
        
        self.addLink(c3, a1)
        self.addLink(c3, a3)
        self.addLink(c3, a5)
        self.addLink(c3, a7)
        

topos = {'mytopo': (lambda: MyTopo())}
