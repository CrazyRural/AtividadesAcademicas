import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;


public class AdicionarDepts {

	public JFrame frame;
	private JTextField textField;
	private JTextField nome;

	public AdicionarDepts() {

		frame = new JFrame();
		frame.setBounds(300, 100, 800, 600);
		frame.setTitle("Adicionar Departamentos");
		frame.setResizable(false);
		
		JPanel panel = new JPanel();
		frame.getContentPane().add(panel, BorderLayout.NORTH);
		
		JPanel panel_1 = new JPanel();
		frame.getContentPane().add(panel_1, BorderLayout.CENTER);
		panel_1.setLayout(null);
		
		JLabel lblNome = new JLabel("Nome:");
		lblNome.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblNome.setBounds(48, 81, 200, 14);
		panel_1.add(lblNome);
		
		nome = new JTextField();
		nome.setBounds(98, 80, 497, 20);
		panel_1.add(nome);
		nome.setColumns(10);

		
		
		JLabel codigoCurso = new JLabel("Sigla do Departamento:");
		codigoCurso.setFont(new Font("Tahoma", Font.PLAIN, 14));
		codigoCurso.setBounds(48,152,150,22);
		panel_1.add(codigoCurso);
		
		textField = new JTextField();
		textField.setBounds(205, 155, 86, 20);
		panel_1.add(textField);
		textField.setColumns(10);
		
		JLabel lblAdicionandoFuncionario = new JLabel("Adicionar Departamento");
		lblAdicionandoFuncionario.setFont(new Font("Tahoma", Font.PLAIN, 20));
		lblAdicionandoFuncionario.setBounds(290, 22, 230, 23);
		panel_1.add(lblAdicionandoFuncionario);

				

		
		JButton bOK = new JButton("Criar");
		bOK.setBounds(340, 517, 89, 23);
		panel_1.add(bOK);
		bOK.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				addCurso();
			}
		});
		}
		public void addCurso(){
		try{	
			Departamento novodept = new Departamento(nome.getText(),textField.getText());
			novodept.setNome(nome.getText());
			novodept.setCodigoDepartamento(textField.getText());
			TelaPrincipal.db.getDept().add(novodept);
			TelaPrincipal.tabela3.preenche();
			frame.dispose();
		}catch(Exception e){
			JOptionPane.showMessageDialog(frame, "Ainda há Campos em Branco", "Erro", JOptionPane.ERROR_MESSAGE);
		}
		}

}
