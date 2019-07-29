#Projector Analysis

This directory is to analyze the light intensity at different points of a projectors field of view.

The table s 8 feet by 8 feet and has two projectors making up two 4 by 8 feet sections.

To get data of the light intensity, I projected all white, grey, or black on the table and took 50 light measurements at 36 different spots (18 for each projector) for 3 different bots.

projector\_analysis reads a .txt file (projector\_analysis.txt) and creates a BOT class everytime the words "BOT" are read. Then, a "color" struct is created each time a different color is read ("White", "Grey", or "Black"). Then, each time a different position is read ("POS" followed by a number), a position struct is created. Each position struct has 50 measurements in it. Each bot will have 3 colors, each color has 26 positions, and each position has 50 measurements. Therefore, there are 3*26*50 = 3,900 measurements total.
