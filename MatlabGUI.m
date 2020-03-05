classdef app2 < matlab.apps.AppBase

    % Properties that correspond to app components
    properties (Access = public)
        UIFigure            matlab.ui.Figure
        HeaterControlLabel  matlab.ui.control.Label
        HighSliderLabel     matlab.ui.control.Label
        HighSlider          matlab.ui.control.Slider
        LowSliderLabel      matlab.ui.control.Label
        LowSlider           matlab.ui.control.Slider
        ChangeValuesButton  matlab.ui.control.Button
    end

    % Callbacks that handle component events
    methods (Access = private)

        % Button pushed function: ChangeValuesButton
        function ChangeValuesButtonPushed(app, event)
            fprintf('Temperature High = %f', app.HighSlider.Value );
            fprintf('Temperature Low = %f', app.LowSlider.Value );
        end
    end

    % Component initialization
    methods (Access = private)

        % Create UIFigure and components
        function createComponents(app)

            % Create UIFigure and hide until all components are created
            app.UIFigure = uifigure('Visible', 'off');
            app.UIFigure.Position = [100 100 324 314];
            app.UIFigure.Name = 'UI Figure';

            % Create HeaterControlLabel
            app.HeaterControlLabel = uilabel(app.UIFigure);
            app.HeaterControlLabel.HorizontalAlignment = 'center';
            app.HeaterControlLabel.FontSize = 15;
            app.HeaterControlLabel.Position = [109 270 107 22];
            app.HeaterControlLabel.Text = 'Heater Control ';

            % Create HighSliderLabel
            app.HighSliderLabel = uilabel(app.UIFigure);
            app.HighSliderLabel.HorizontalAlignment = 'right';
            app.HighSliderLabel.Position = [56 203 34 22];
            app.HighSliderLabel.Text = 'High ';

            % Create HighSlider
            app.HighSlider = uislider(app.UIFigure);
            app.HighSlider.Limits = [10 30];
            app.HighSlider.Position = [111 212 156 3];
            app.HighSlider.Value = 10;

            % Create LowSliderLabel
            app.LowSliderLabel = uilabel(app.UIFigure);
            app.LowSliderLabel.HorizontalAlignment = 'right';
            app.LowSliderLabel.Position = [56 130 28 22];
            app.LowSliderLabel.Text = 'Low';

            % Create LowSlider
            app.LowSlider = uislider(app.UIFigure);
            app.LowSlider.Limits = [10 30];
            app.LowSlider.Position = [105 139 162 3];
            app.LowSlider.Value = 10;

            % Create ChangeValuesButton
            app.ChangeValuesButton = uibutton(app.UIFigure, 'push');
            app.ChangeValuesButton.ButtonPushedFcn = createCallbackFcn(app, @ChangeValuesButtonPushed, true);
            app.ChangeValuesButton.Position = [178 51 100 22];
            app.ChangeValuesButton.Text = 'Change Values';

            % Show the figure after all components are created
            app.UIFigure.Visible = 'on';
        end
    end

    % App creation and deletion
    methods (Access = public)

        % Construct app
        function app = app2

            % Create UIFigure and components
            createComponents(app)

            % Register the app with App Designer
            registerApp(app, app.UIFigure)

            if nargout == 0
                clear app
            end
        end

        % Code that executes before app deletion
        function delete(app)

            % Delete UIFigure when app is deleted
            delete(app.UIFigure)
        end
    end
end
