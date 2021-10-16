#pragma once
#include "imgui.h"
#include "loguru.hpp"
namespace DebugUI
{
    struct  DebugConsole
    {
        ImGuiTextBuffer	Buffer;
        ImGuiTextFilter	Filter;
        ImVector<int>	LineOffset;
        bool			ScrollToBottom;



        void Clear()
        {
            Buffer.clear();
            LineOffset.clear();
        }







        void    AddLog(const char* fmt, ...)// IM_PRINTFARGS(2)
        {
            int old_size = Buffer.size();
            va_list args;
            va_start(args, fmt);
            Buffer.appendfv(fmt, args);
            va_end(args);
            for (int new_size = Buffer.size(); old_size < new_size; old_size++)
                if (Buffer[old_size] == '\n')
                    LineOffset.push_back(old_size);
            ScrollToBottom = true;
        }

        void    Draw(const char* title, bool* p_opened = NULL)
        {
            ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
            ImGui::Begin(title, p_opened);
            if (ImGui::Button("Clear")) Clear();
            ImGui::SameLine();
            bool copy = ImGui::Button("Copy");
            ImGui::SameLine();
            Filter.Draw("Filter", -100.0f);
            ImGui::Separator();
            ImGui::BeginChild("scrolling");
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
            if (copy) ImGui::LogToClipboard();

            if (Filter.IsActive())
            {
                const char* buf_begin = Buffer.begin();
                const char* line = buf_begin;

                for (int line_no = 0; line != NULL; line_no++)
                {
                    const char* line_end = (line_no < LineOffset.Size) ? buf_begin + LineOffset[line_no] : NULL;
                    if (Filter.PassFilter(line, line_end))
                        ImGui::TextWrapped(line, line_end);

                    line = line_end && line_end[1] ? line_end + 1 : NULL;
                }
            }
            else
            {
                ImGui::TextWrapped(Buffer.begin());
            }

            //if (ScrollToBottom)
            //    ImGui::SetScrollHere(1.0f);

            ScrollToBottom = false;

            ImGui::PopStyleVar();
            ImGui::EndChild();
            ImGui::End();
        }

    };
}
