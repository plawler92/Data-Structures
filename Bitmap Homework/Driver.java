
public class Driver{
	public static void main(String args[]){		
		Icon i1 = new Icon(100,100);
		for(int i = 0; i < 100; i++){
			for(int j = 0; j < 100; j++){
				if(i % 2 == 0){
					if(j % 2 == 0)
						i1.setRGB(i, j, 255, 0, 0);					
					else
						i1.setRGB(i, j, 0, 255, 0);
				}
				else{
					if(j % 2 == 0)
						i1.setRGB(i, j, 0, 255, 0);
					else
						i1.setRGB(i, j, 255, 0, 0);
				}				
			}
		}

		i1.saveBMP("test.bmp");
		i1.printHexValues();		
	}
}
