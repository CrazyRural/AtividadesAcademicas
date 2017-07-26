import javax.swing.JFrame;
import javax.swing.JPanel;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JLabel;
import javax.swing.JComboBox;
import javax.swing.JButton;


public class OpcaoAlmoco extends JFrame {

	JFrame frame;
	static JComboBox comboBox;
	static JComboBox comboBox_1;
	static JComboBox comboBox_2;
	static JComboBox comboBox_3;
	static JComboBox comboBox_4;
	static JComboBox comboBox_5;
	String[] principal = {"Arroz Branco","Arroz Integral","Arroz Agulinha","Arroz Parbolizado"};
	String[] principal1 = {"Feijão Preto","Feijão Branco","Feijão Carioquinha","Feijão Fradinho"};
	String[] acompanhamento = {"Carne Assada","Bife de Panela","Carre ao Molho","Steak de Frango","Carne Moída"};
	String[] acompanhamento1={"Purê de Batata","Purê de Aipim","Polenta","Farofa c/ Molho a Campanha"};
	String[] opcaoVegetariana = {"Tofu","Carne de Soja","Omelete de Legumes","Quiche de Queijo"};
	String[] salada = {"Acelga","Alface","Agrião","Couve","Bertalha","Couve","Espinafre","Rúcula"};
	private JButton btnSalvar;
	
	public OpcaoAlmoco() {
		frame = new JFrame();
		frame.setBounds(400, 300, 450, 300);
		frame.setResizable(false);
		frame.setTitle("Opções para o Almoço ");
		
		JPanel panel = new JPanel();
		frame.getContentPane().add(panel, BorderLayout.CENTER);
		panel.setLayout(null);
		
		JLabel lblPratosPrincipais = new JLabel("Pratos Principais:");
		lblPratosPrincipais.setBounds(10, 25, 90, 14);
		panel.add(lblPratosPrincipais);

		//criando as combo boxs
		comboBox = new JComboBox(principal);
		comboBox.setBounds(10, 50, 90, 20);
		panel.add(comboBox);
		
		comboBox_1 = new JComboBox(principal1);
		comboBox_1.setBounds(10, 106, 90, 20);
		panel.add(comboBox_1);
		
		JLabel lblAcompanhamento = new JLabel("Acompanhamento:");
		lblAcompanhamento.setBounds(172, 25, 100, 14);
		panel.add(lblAcompanhamento);
		
		comboBox_2 = new JComboBox(acompanhamento);
		comboBox_2.setBounds(172, 50, 90, 20);
		panel.add(comboBox_2);
		
		comboBox_3 = new JComboBox(acompanhamento1);
		comboBox_3.setBounds(172, 106, 90, 20);
		panel.add(comboBox_3);
		
		JLabel lblVegetais = new JLabel("Vegetais:");
		lblVegetais.setBounds(320, 25, 55, 14);
		panel.add(lblVegetais);
		
		comboBox_4 = new JComboBox(salada);
		comboBox_4.setBounds(320, 50, 100, 20);
		panel.add(comboBox_4);
		
		JLabel lblOpoVegetariana = new JLabel("Opção Vegetariana:");
		lblOpoVegetariana.setBounds(320, 81, 110, 14);
		panel.add(lblOpoVegetariana);
				
		comboBox_5 = new JComboBox(opcaoVegetariana);
		comboBox_5.setBounds(320, 106, 100, 20);
		panel.add(comboBox_5);
		
		btnSalvar = new JButton("SALVAR");
		btnSalvar.setBounds(161, 159, 111, 45);
		panel.add(btnSalvar);		
		btnSalvar.addActionListener(new ActionListener() {			
			@Override
			public void actionPerformed(ActionEvent e) {
				salvarClick();
				
			}
		});
		
		/*finalList[0] = "Prato Principal";
		finalList[1] = comboBox.getSelectedItem().toString();
		finalList[1] = comboBox_1.getSelectedItem().toString();
		finalList[2] = "Acompanhamentos";
		finalList[3] = comboBox_2.getSelectedItem().toString();
		finalList[4] = comboBox_3.getSelectedItem().toString();
		finalList[5] = "Salada";
		finalList[6] = comboBox_4.getSelectedItem().toString();
		finalList[7] = "Opção Vegetariana";
		finalList[8] = comboBox_5.getSelectedItem().toString();
	*/}
	public void salvarClick(){
		frame.dispose();
	}
}
