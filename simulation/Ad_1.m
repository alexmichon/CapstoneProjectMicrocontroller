function output = Ad_1(R,p)
P_head = [0 -p(3) p(2);
         p(3) 0  -p(1);
         -p(2) p(1) 0];
output = [R', -R'*P_head;
          zeros(3,3),R];
end

