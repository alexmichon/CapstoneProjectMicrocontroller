function output = Ad(R,p)
P_head = [0 -p(3) p(2);
         p(3) 0  -p(1);
         -p(2) p(1) 0];
output = [R,         P_head*R;
          zeros(3,3),R];
end

