import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;


public class AdicionarCurso {

	public JFrame frame;
	private JTextField nome;
	private JTextField textField;
	public static JComboBox<Object> comboBox;
	
	public AdicionarCurso() {
	
		frame = new JFrame();
		frame.setBounds(300, 100,800, 600);
		frame.setTitle("Adicionar Curso");
		frame.setResizable(false);
		
		JPanel panel = new JPanel();
		frame.getContentPane().add(panel, BorderLayout.NORTH);
		
		JPanel panel_1 = new JPanel();
		frame.getContentPane().add(panel_1, BorderLayout.CENTER);
		panel_1.setLayout(null);
		
		JLabel lblNome = new JLabel("Nome:");
		lblNome.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblNome.setBounds(48, 81, 103, 14);
		panel_1.add(lblNome);
		
		nome = new JTextField();
		nome.setBounds(98, 80, 497, 20);
		panel_1.add(nome);
		nome.setColumns(10);

		JLabel lblDepartamento = new JLabel("Departamento:");
		lblDepartamento.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblDepartamento.setBounds(48, 220, 103, 22);
		panel_1.add(lblDepartamento);
		
		JLabel codigoCurso = new JLabel("Sigla do Curso:");
		codigoCurso.setFont(new Font("Tahoma", Font.PLAIN, 14));
		codigoCurso.setBounds(48,152,103,22);
		panel_1.add(codigoCurso);
		
		
		textField = new JTextField();
		textField.setBounds(161, 155, 86, 20);
		panel_1.add(textField);
		textField.setColumns(10);
		
		JButton bOK = new JButton("Criar");
		bOK.setBounds(340, 517, 89, 23);
		panel_1.add(bOK);
		
		String [] listaDept = new String[TelaPrincipal.db.getDept().size()];
		
		for (int i = 0; i < TelaPrincipal.db.getDept().size(); i++) {
			listaDept[i] = TelaPrincipal.db.getDept().get(i).getNome();
			
		}
		comboBox = new JComboBox<Object>(listaDept);
		comboBox.setBounds(148, 223, 295, 20);
		panel_1.add(comboBox);		
		
		JLabel lblAdicionandoFuncionario = new JLabel("Adicionar Curso");
		lblAdicionandoFuncionario.setFont(new Font("Tahoma", Font.PLAIN, 20));
		lblAdicionandoFuncionario.setBounds(290, 22, 216, 23);
		panel_1.add(lblAdicionandoFuncionario);

		
		bOK.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				addCurso();
			}
		});
	}
	public void addCurso(){
		try{
			Curso novocurso = new Curso(nome.getText(),textField.getText(),comboBox.getSelectedItem().toString());
			novocurso.setNome(nome.getText());
			novocurso.setCodigoCurso(textField.getText());
			novocurso.setDepartamento(comboBox.getSelectedItem().toString());
			TelaPrincipal.db.getCurso().add(novocurso);
			TelaPrincipal.tabela2.preenche();
			frame.dispose();
	}catch(Exception e){
		JOptionPane.showMessageDialog(frame, "Ainda há Campos em Branco", "Erro", JOptionPane.ERROR_MESSAGE);
		}
	}
}


