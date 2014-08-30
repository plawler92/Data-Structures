public class Pixel{		

		private int rgb;

		//sets rgb to a rgb value if none specified
		public Pixel(){
			rgb = 13161583;
		}		

		//sets rgb to a specific rgb value
		public Pixel(int r, int g, int b){
			setRed(r);
			setGreen(g);
			setBlue(b);
		}

		//returns rgb value
		public int getRGB(){
			return rgb;
		}

		//sets r in rgb
		public void setRed(int r){
			rgb = r;
		}

		//shifts over two sets of 8 bits to get the start of the red value
		public int getRed(){
			return (rgb>>16) & 0xFF;
		}

		//sets g in rgb by shifting existing bits over 8 spots
		public void setGreen(int g){
			rgb = (rgb<<8) + g;
		}

		//shifts over 1 set of 8 bit to get the start of green values
		public int getGreen(){
			return (rgb>>8) & 0xFF;
		}

		//sets b in rgb by shifting existing bits over 8 spots
		public void setBlue(int b){
			rgb = (rgb << 8) + b;
		}

		//gets blue from rgb
		public int getBlue(){
			return rgb & 0xFF;
		}

		//gets rgb in hex form
		public String getHex(){
			String hex_val = Integer.toHexString(rgb);				
			return hex_val;
		}

}