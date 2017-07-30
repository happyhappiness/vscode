; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string_sprintf.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive_string = type { i8*, i64, i64 }
%struct.__va_list_tag = type { i32, i32, i8*, i8* }

@.str = private unnamed_addr constant [14 x i8] c"Out of memory\00", align 1
@.str.1 = private unnamed_addr constant [7 x i32] [i32 40, i32 110, i32 117, i32 108, i32 108, i32 41, i32 0], align 4
@.str.2 = private unnamed_addr constant [7 x i8] c"(null)\00", align 1
@append_uint.digits = internal global i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.3, i32 0, i32 0), align 8
@.str.3 = private unnamed_addr constant [17 x i8] c"0123456789abcdef\00", align 1

; Function Attrs: nounwind uwtable
define void @archive_string_sprintf(%struct.archive_string* %as, i8* %fmt, ...) #0 !dbg !10 {
entry:
  %as.addr = alloca %struct.archive_string*, align 8
  %fmt.addr = alloca i8*, align 8
  %ap = alloca [1 x %struct.__va_list_tag], align 16
  store %struct.archive_string* %as, %struct.archive_string** %as.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %as.addr, metadata !49, metadata !50), !dbg !51
  store i8* %fmt, i8** %fmt.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %fmt.addr, metadata !52, metadata !50), !dbg !53
  call void @llvm.dbg.declare(metadata [1 x %struct.__va_list_tag]* %ap, metadata !54, metadata !50), !dbg !63
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap, i32 0, i32 0, !dbg !64
  %arraydecay1 = bitcast %struct.__va_list_tag* %arraydecay to i8*, !dbg !64
  call void @llvm.va_start(i8* %arraydecay1), !dbg !64
  %0 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !65
  %1 = load i8*, i8** %fmt.addr, align 8, !dbg !66
  %arraydecay2 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap, i32 0, i32 0, !dbg !67
  call void @archive_string_vsprintf(%struct.archive_string* %0, i8* %1, %struct.__va_list_tag* %arraydecay2), !dbg !68
  %arraydecay3 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap, i32 0, i32 0, !dbg !69
  %arraydecay34 = bitcast %struct.__va_list_tag* %arraydecay3 to i8*, !dbg !69
  call void @llvm.va_end(i8* %arraydecay34), !dbg !69
  ret void, !dbg !70
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #2

; Function Attrs: nounwind uwtable
define void @archive_string_vsprintf(%struct.archive_string* %as, i8* %fmt, %struct.__va_list_tag* %ap) #0 !dbg !25 {
entry:
  %as.addr = alloca %struct.archive_string*, align 8
  %fmt.addr = alloca i8*, align 8
  %ap.addr = alloca %struct.__va_list_tag*, align 8
  %long_flag = alloca i8, align 1
  %s = alloca i64, align 8
  %u = alloca i64, align 8
  %p = alloca i8*, align 8
  %p2 = alloca i8*, align 8
  %pw = alloca i32*, align 8
  %saved_p = alloca i8*, align 8
  store %struct.archive_string* %as, %struct.archive_string** %as.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %as.addr, metadata !71, metadata !50), !dbg !72
  store i8* %fmt, i8** %fmt.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %fmt.addr, metadata !73, metadata !50), !dbg !74
  store %struct.__va_list_tag* %ap, %struct.__va_list_tag** %ap.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.__va_list_tag** %ap.addr, metadata !75, metadata !50), !dbg !76
  call void @llvm.dbg.declare(metadata i8* %long_flag, metadata !77, metadata !50), !dbg !78
  call void @llvm.dbg.declare(metadata i64* %s, metadata !79, metadata !50), !dbg !80
  call void @llvm.dbg.declare(metadata i64* %u, metadata !81, metadata !50), !dbg !82
  call void @llvm.dbg.declare(metadata i8** %p, metadata !83, metadata !50), !dbg !84
  call void @llvm.dbg.declare(metadata i8** %p2, metadata !85, metadata !50), !dbg !86
  call void @llvm.dbg.declare(metadata i32** %pw, metadata !87, metadata !50), !dbg !92
  %0 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !93
  %call = call %struct.archive_string* @archive_string_ensure(%struct.archive_string* %0, i64 64), !dbg !95
  %cmp = icmp eq %struct.archive_string* %call, null, !dbg !96
  br i1 %cmp, label %if.then, label %if.end, !dbg !97

if.then:                                          ; preds = %entry
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str, i32 0, i32 0)) #7, !dbg !98
  unreachable, !dbg !98

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** %fmt.addr, align 8, !dbg !99
  %cmp1 = icmp eq i8* %1, null, !dbg !101
  br i1 %cmp1, label %if.then2, label %if.end4, !dbg !102

if.then2:                                         ; preds = %if.end
  %2 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !103
  %s3 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %2, i32 0, i32 0, !dbg !105
  %3 = load i8*, i8** %s3, align 8, !dbg !105
  %arrayidx = getelementptr inbounds i8, i8* %3, i64 0, !dbg !103
  store i8 0, i8* %arrayidx, align 1, !dbg !106
  br label %for.end, !dbg !107

if.end4:                                          ; preds = %if.end
  %4 = load i8*, i8** %fmt.addr, align 8, !dbg !108
  store i8* %4, i8** %p, align 8, !dbg !110
  br label %for.cond, !dbg !111

for.cond:                                         ; preds = %for.inc, %if.end4
  %5 = load i8*, i8** %p, align 8, !dbg !112
  %6 = load i8, i8* %5, align 1, !dbg !115
  %conv = sext i8 %6 to i32, !dbg !115
  %cmp5 = icmp ne i32 %conv, 0, !dbg !116
  br i1 %cmp5, label %for.body, label %for.end, !dbg !117

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i8** %saved_p, metadata !118, metadata !50), !dbg !120
  %7 = load i8*, i8** %p, align 8, !dbg !121
  store i8* %7, i8** %saved_p, align 8, !dbg !120
  %8 = load i8*, i8** %p, align 8, !dbg !122
  %9 = load i8, i8* %8, align 1, !dbg !124
  %conv7 = sext i8 %9 to i32, !dbg !124
  %cmp8 = icmp ne i32 %conv7, 37, !dbg !125
  br i1 %cmp8, label %if.then10, label %if.end12, !dbg !126

if.then10:                                        ; preds = %for.body
  %10 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !127
  %11 = load i8*, i8** %p, align 8, !dbg !129
  %12 = load i8, i8* %11, align 1, !dbg !130
  %call11 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %10, i8 signext %12), !dbg !131
  br label %for.inc, !dbg !132

if.end12:                                         ; preds = %for.body
  %13 = load i8*, i8** %p, align 8, !dbg !133
  %incdec.ptr = getelementptr inbounds i8, i8* %13, i32 1, !dbg !133
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !133
  store i8 0, i8* %long_flag, align 1, !dbg !134
  %14 = load i8*, i8** %p, align 8, !dbg !135
  %15 = load i8, i8* %14, align 1, !dbg !136
  %conv13 = sext i8 %15 to i32, !dbg !136
  switch i32 %conv13, label %sw.epilog [
    i32 106, label %sw.bb
    i32 108, label %sw.bb
    i32 122, label %sw.bb
  ], !dbg !137

sw.bb:                                            ; preds = %if.end12, %if.end12, %if.end12
  %16 = load i8*, i8** %p, align 8, !dbg !138
  %17 = load i8, i8* %16, align 1, !dbg !140
  store i8 %17, i8* %long_flag, align 1, !dbg !141
  %18 = load i8*, i8** %p, align 8, !dbg !142
  %incdec.ptr14 = getelementptr inbounds i8, i8* %18, i32 1, !dbg !142
  store i8* %incdec.ptr14, i8** %p, align 8, !dbg !142
  br label %sw.epilog, !dbg !143

sw.epilog:                                        ; preds = %if.end12, %sw.bb
  %19 = load i8*, i8** %p, align 8, !dbg !144
  %20 = load i8, i8* %19, align 1, !dbg !145
  %conv15 = sext i8 %20 to i32, !dbg !145
  switch i32 %conv15, label %sw.default201 [
    i32 37, label %sw.bb16
    i32 99, label %sw.bb18
    i32 100, label %sw.bb22
    i32 115, label %sw.bb73
    i32 83, label %sw.bb118
    i32 111, label %sw.bb144
    i32 117, label %sw.bb144
    i32 120, label %sw.bb144
    i32 88, label %sw.bb144
  ], !dbg !146

sw.bb16:                                          ; preds = %sw.epilog
  %21 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !147
  %call17 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %21, i8 signext 37), !dbg !149
  br label %sw.epilog203, !dbg !150

sw.bb18:                                          ; preds = %sw.epilog
  %22 = load %struct.__va_list_tag*, %struct.__va_list_tag** %ap.addr, align 8, !dbg !151
  %gp_offset_p = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %22, i32 0, i32 0, !dbg !151
  %gp_offset = load i32, i32* %gp_offset_p, align 8, !dbg !151
  %fits_in_gp = icmp ule i32 %gp_offset, 40, !dbg !151
  br i1 %fits_in_gp, label %vaarg.in_reg, label %vaarg.in_mem, !dbg !151

vaarg.in_reg:                                     ; preds = %sw.bb18
  %23 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %22, i32 0, i32 3, !dbg !152
  %reg_save_area = load i8*, i8** %23, align 8, !dbg !152
  %24 = getelementptr i8, i8* %reg_save_area, i32 %gp_offset, !dbg !152
  %25 = bitcast i8* %24 to i32*, !dbg !152
  %26 = add i32 %gp_offset, 8, !dbg !152
  store i32 %26, i32* %gp_offset_p, align 8, !dbg !152
  br label %vaarg.end, !dbg !152

vaarg.in_mem:                                     ; preds = %sw.bb18
  %overflow_arg_area_p = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %22, i32 0, i32 2, !dbg !154
  %overflow_arg_area = load i8*, i8** %overflow_arg_area_p, align 8, !dbg !154
  %27 = bitcast i8* %overflow_arg_area to i32*, !dbg !154
  %overflow_arg_area.next = getelementptr i8, i8* %overflow_arg_area, i32 8, !dbg !154
  store i8* %overflow_arg_area.next, i8** %overflow_arg_area_p, align 8, !dbg !154
  br label %vaarg.end, !dbg !154

vaarg.end:                                        ; preds = %vaarg.in_mem, %vaarg.in_reg
  %vaarg.addr = phi i32* [ %25, %vaarg.in_reg ], [ %27, %vaarg.in_mem ], !dbg !156
  %28 = load i32, i32* %vaarg.addr, align 4, !dbg !156
  %conv19 = sext i32 %28 to i64, !dbg !156
  store i64 %conv19, i64* %s, align 8, !dbg !158
  %29 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !159
  %30 = load i64, i64* %s, align 8, !dbg !160
  %conv20 = trunc i64 %30 to i8, !dbg !161
  %call21 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %29, i8 signext %conv20), !dbg !162
  br label %sw.epilog203, !dbg !163

sw.bb22:                                          ; preds = %sw.epilog
  %31 = load i8, i8* %long_flag, align 1, !dbg !164
  %conv23 = sext i8 %31 to i32, !dbg !164
  switch i32 %conv23, label %sw.default [
    i32 106, label %sw.bb24
    i32 108, label %sw.bb36
    i32 122, label %sw.bb48
  ], !dbg !165

sw.bb24:                                          ; preds = %sw.bb22
  %32 = load %struct.__va_list_tag*, %struct.__va_list_tag** %ap.addr, align 8, !dbg !166
  %gp_offset_p25 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %32, i32 0, i32 0, !dbg !166
  %gp_offset26 = load i32, i32* %gp_offset_p25, align 8, !dbg !166
  %fits_in_gp27 = icmp ule i32 %gp_offset26, 40, !dbg !166
  br i1 %fits_in_gp27, label %vaarg.in_reg28, label %vaarg.in_mem30, !dbg !166

vaarg.in_reg28:                                   ; preds = %sw.bb24
  %33 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %32, i32 0, i32 3, !dbg !168
  %reg_save_area29 = load i8*, i8** %33, align 8, !dbg !168
  %34 = getelementptr i8, i8* %reg_save_area29, i32 %gp_offset26, !dbg !168
  %35 = bitcast i8* %34 to i64*, !dbg !168
  %36 = add i32 %gp_offset26, 8, !dbg !168
  store i32 %36, i32* %gp_offset_p25, align 8, !dbg !168
  br label %vaarg.end34, !dbg !168

vaarg.in_mem30:                                   ; preds = %sw.bb24
  %overflow_arg_area_p31 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %32, i32 0, i32 2, !dbg !170
  %overflow_arg_area32 = load i8*, i8** %overflow_arg_area_p31, align 8, !dbg !170
  %37 = bitcast i8* %overflow_arg_area32 to i64*, !dbg !170
  %overflow_arg_area.next33 = getelementptr i8, i8* %overflow_arg_area32, i32 8, !dbg !170
  store i8* %overflow_arg_area.next33, i8** %overflow_arg_area_p31, align 8, !dbg !170
  br label %vaarg.end34, !dbg !170

vaarg.end34:                                      ; preds = %vaarg.in_mem30, %vaarg.in_reg28
  %vaarg.addr35 = phi i64* [ %35, %vaarg.in_reg28 ], [ %37, %vaarg.in_mem30 ], !dbg !172
  %38 = load i64, i64* %vaarg.addr35, align 8, !dbg !172
  store i64 %38, i64* %s, align 8, !dbg !174
  br label %sw.epilog72, !dbg !175

sw.bb36:                                          ; preds = %sw.bb22
  %39 = load %struct.__va_list_tag*, %struct.__va_list_tag** %ap.addr, align 8, !dbg !176
  %gp_offset_p37 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %39, i32 0, i32 0, !dbg !176
  %gp_offset38 = load i32, i32* %gp_offset_p37, align 8, !dbg !176
  %fits_in_gp39 = icmp ule i32 %gp_offset38, 40, !dbg !176
  br i1 %fits_in_gp39, label %vaarg.in_reg40, label %vaarg.in_mem42, !dbg !176

vaarg.in_reg40:                                   ; preds = %sw.bb36
  %40 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %39, i32 0, i32 3, !dbg !177
  %reg_save_area41 = load i8*, i8** %40, align 8, !dbg !177
  %41 = getelementptr i8, i8* %reg_save_area41, i32 %gp_offset38, !dbg !177
  %42 = bitcast i8* %41 to i64*, !dbg !177
  %43 = add i32 %gp_offset38, 8, !dbg !177
  store i32 %43, i32* %gp_offset_p37, align 8, !dbg !177
  br label %vaarg.end46, !dbg !177

vaarg.in_mem42:                                   ; preds = %sw.bb36
  %overflow_arg_area_p43 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %39, i32 0, i32 2, !dbg !178
  %overflow_arg_area44 = load i8*, i8** %overflow_arg_area_p43, align 8, !dbg !178
  %44 = bitcast i8* %overflow_arg_area44 to i64*, !dbg !178
  %overflow_arg_area.next45 = getelementptr i8, i8* %overflow_arg_area44, i32 8, !dbg !178
  store i8* %overflow_arg_area.next45, i8** %overflow_arg_area_p43, align 8, !dbg !178
  br label %vaarg.end46, !dbg !178

vaarg.end46:                                      ; preds = %vaarg.in_mem42, %vaarg.in_reg40
  %vaarg.addr47 = phi i64* [ %42, %vaarg.in_reg40 ], [ %44, %vaarg.in_mem42 ], !dbg !179
  %45 = load i64, i64* %vaarg.addr47, align 8, !dbg !179
  store i64 %45, i64* %s, align 8, !dbg !180
  br label %sw.epilog72, !dbg !181

sw.bb48:                                          ; preds = %sw.bb22
  %46 = load %struct.__va_list_tag*, %struct.__va_list_tag** %ap.addr, align 8, !dbg !182
  %gp_offset_p49 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %46, i32 0, i32 0, !dbg !182
  %gp_offset50 = load i32, i32* %gp_offset_p49, align 8, !dbg !182
  %fits_in_gp51 = icmp ule i32 %gp_offset50, 40, !dbg !182
  br i1 %fits_in_gp51, label %vaarg.in_reg52, label %vaarg.in_mem54, !dbg !182

vaarg.in_reg52:                                   ; preds = %sw.bb48
  %47 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %46, i32 0, i32 3, !dbg !183
  %reg_save_area53 = load i8*, i8** %47, align 8, !dbg !183
  %48 = getelementptr i8, i8* %reg_save_area53, i32 %gp_offset50, !dbg !183
  %49 = bitcast i8* %48 to i64*, !dbg !183
  %50 = add i32 %gp_offset50, 8, !dbg !183
  store i32 %50, i32* %gp_offset_p49, align 8, !dbg !183
  br label %vaarg.end58, !dbg !183

vaarg.in_mem54:                                   ; preds = %sw.bb48
  %overflow_arg_area_p55 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %46, i32 0, i32 2, !dbg !184
  %overflow_arg_area56 = load i8*, i8** %overflow_arg_area_p55, align 8, !dbg !184
  %51 = bitcast i8* %overflow_arg_area56 to i64*, !dbg !184
  %overflow_arg_area.next57 = getelementptr i8, i8* %overflow_arg_area56, i32 8, !dbg !184
  store i8* %overflow_arg_area.next57, i8** %overflow_arg_area_p55, align 8, !dbg !184
  br label %vaarg.end58, !dbg !184

vaarg.end58:                                      ; preds = %vaarg.in_mem54, %vaarg.in_reg52
  %vaarg.addr59 = phi i64* [ %49, %vaarg.in_reg52 ], [ %51, %vaarg.in_mem54 ], !dbg !185
  %52 = load i64, i64* %vaarg.addr59, align 8, !dbg !185
  store i64 %52, i64* %s, align 8, !dbg !186
  br label %sw.epilog72, !dbg !187

sw.default:                                       ; preds = %sw.bb22
  %53 = load %struct.__va_list_tag*, %struct.__va_list_tag** %ap.addr, align 8, !dbg !188
  %gp_offset_p60 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %53, i32 0, i32 0, !dbg !188
  %gp_offset61 = load i32, i32* %gp_offset_p60, align 8, !dbg !188
  %fits_in_gp62 = icmp ule i32 %gp_offset61, 40, !dbg !188
  br i1 %fits_in_gp62, label %vaarg.in_reg63, label %vaarg.in_mem65, !dbg !188

vaarg.in_reg63:                                   ; preds = %sw.default
  %54 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %53, i32 0, i32 3, !dbg !189
  %reg_save_area64 = load i8*, i8** %54, align 8, !dbg !189
  %55 = getelementptr i8, i8* %reg_save_area64, i32 %gp_offset61, !dbg !189
  %56 = bitcast i8* %55 to i32*, !dbg !189
  %57 = add i32 %gp_offset61, 8, !dbg !189
  store i32 %57, i32* %gp_offset_p60, align 8, !dbg !189
  br label %vaarg.end69, !dbg !189

vaarg.in_mem65:                                   ; preds = %sw.default
  %overflow_arg_area_p66 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %53, i32 0, i32 2, !dbg !190
  %overflow_arg_area67 = load i8*, i8** %overflow_arg_area_p66, align 8, !dbg !190
  %58 = bitcast i8* %overflow_arg_area67 to i32*, !dbg !190
  %overflow_arg_area.next68 = getelementptr i8, i8* %overflow_arg_area67, i32 8, !dbg !190
  store i8* %overflow_arg_area.next68, i8** %overflow_arg_area_p66, align 8, !dbg !190
  br label %vaarg.end69, !dbg !190

vaarg.end69:                                      ; preds = %vaarg.in_mem65, %vaarg.in_reg63
  %vaarg.addr70 = phi i32* [ %56, %vaarg.in_reg63 ], [ %58, %vaarg.in_mem65 ], !dbg !191
  %59 = load i32, i32* %vaarg.addr70, align 4, !dbg !191
  %conv71 = sext i32 %59 to i64, !dbg !191
  store i64 %conv71, i64* %s, align 8, !dbg !192
  br label %sw.epilog72, !dbg !193

sw.epilog72:                                      ; preds = %vaarg.end69, %vaarg.end58, %vaarg.end46, %vaarg.end34
  %60 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !194
  %61 = load i64, i64* %s, align 8, !dbg !195
  call void @append_int(%struct.archive_string* %60, i64 %61, i32 10), !dbg !196
  br label %sw.epilog203, !dbg !197

sw.bb73:                                          ; preds = %sw.epilog
  %62 = load i8, i8* %long_flag, align 1, !dbg !198
  %conv74 = sext i8 %62 to i32, !dbg !198
  switch i32 %conv74, label %sw.default100 [
    i32 108, label %sw.bb75
  ], !dbg !199

sw.bb75:                                          ; preds = %sw.bb73
  %63 = load %struct.__va_list_tag*, %struct.__va_list_tag** %ap.addr, align 8, !dbg !200
  %gp_offset_p76 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %63, i32 0, i32 0, !dbg !200
  %gp_offset77 = load i32, i32* %gp_offset_p76, align 8, !dbg !200
  %fits_in_gp78 = icmp ule i32 %gp_offset77, 40, !dbg !200
  br i1 %fits_in_gp78, label %vaarg.in_reg79, label %vaarg.in_mem81, !dbg !200

vaarg.in_reg79:                                   ; preds = %sw.bb75
  %64 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %63, i32 0, i32 3, !dbg !202
  %reg_save_area80 = load i8*, i8** %64, align 8, !dbg !202
  %65 = getelementptr i8, i8* %reg_save_area80, i32 %gp_offset77, !dbg !202
  %66 = bitcast i8* %65 to i32**, !dbg !202
  %67 = add i32 %gp_offset77, 8, !dbg !202
  store i32 %67, i32* %gp_offset_p76, align 8, !dbg !202
  br label %vaarg.end85, !dbg !202

vaarg.in_mem81:                                   ; preds = %sw.bb75
  %overflow_arg_area_p82 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %63, i32 0, i32 2, !dbg !204
  %overflow_arg_area83 = load i8*, i8** %overflow_arg_area_p82, align 8, !dbg !204
  %68 = bitcast i8* %overflow_arg_area83 to i32**, !dbg !204
  %overflow_arg_area.next84 = getelementptr i8, i8* %overflow_arg_area83, i32 8, !dbg !204
  store i8* %overflow_arg_area.next84, i8** %overflow_arg_area_p82, align 8, !dbg !204
  br label %vaarg.end85, !dbg !204

vaarg.end85:                                      ; preds = %vaarg.in_mem81, %vaarg.in_reg79
  %vaarg.addr86 = phi i32** [ %66, %vaarg.in_reg79 ], [ %68, %vaarg.in_mem81 ], !dbg !206
  %69 = load i32*, i32** %vaarg.addr86, align 8, !dbg !206
  store i32* %69, i32** %pw, align 8, !dbg !208
  %70 = load i32*, i32** %pw, align 8, !dbg !209
  %cmp87 = icmp eq i32* %70, null, !dbg !211
  br i1 %cmp87, label %if.then89, label %if.end90, !dbg !212

if.then89:                                        ; preds = %vaarg.end85
  store i32* getelementptr inbounds ([7 x i32], [7 x i32]* @.str.1, i32 0, i32 0), i32** %pw, align 8, !dbg !213
  br label %if.end90, !dbg !214

if.end90:                                         ; preds = %if.then89, %vaarg.end85
  %71 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !215
  %72 = load i32*, i32** %pw, align 8, !dbg !217
  %73 = load i32*, i32** %pw, align 8, !dbg !218
  %call91 = call i64 @wcslen(i32* %73) #8, !dbg !219
  %call92 = call i32 @archive_string_append_from_wcs(%struct.archive_string* %71, i32* %72, i64 %call91), !dbg !220
  %cmp93 = icmp ne i32 %call92, 0, !dbg !221
  br i1 %cmp93, label %land.lhs.true, label %if.end99, !dbg !222

land.lhs.true:                                    ; preds = %if.end90
  %call95 = call i32* @__errno_location() #1, !dbg !223
  %74 = load i32, i32* %call95, align 4, !dbg !223
  %cmp96 = icmp eq i32 %74, 12, !dbg !225
  br i1 %cmp96, label %if.then98, label %if.end99, !dbg !226

if.then98:                                        ; preds = %land.lhs.true
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str, i32 0, i32 0)) #7, !dbg !227
  unreachable, !dbg !227

if.end99:                                         ; preds = %land.lhs.true, %if.end90
  br label %sw.epilog117, !dbg !228

sw.default100:                                    ; preds = %sw.bb73
  %75 = load %struct.__va_list_tag*, %struct.__va_list_tag** %ap.addr, align 8, !dbg !229
  %gp_offset_p101 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %75, i32 0, i32 0, !dbg !229
  %gp_offset102 = load i32, i32* %gp_offset_p101, align 8, !dbg !229
  %fits_in_gp103 = icmp ule i32 %gp_offset102, 40, !dbg !229
  br i1 %fits_in_gp103, label %vaarg.in_reg104, label %vaarg.in_mem106, !dbg !229

vaarg.in_reg104:                                  ; preds = %sw.default100
  %76 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %75, i32 0, i32 3, !dbg !230
  %reg_save_area105 = load i8*, i8** %76, align 8, !dbg !230
  %77 = getelementptr i8, i8* %reg_save_area105, i32 %gp_offset102, !dbg !230
  %78 = bitcast i8* %77 to i8**, !dbg !230
  %79 = add i32 %gp_offset102, 8, !dbg !230
  store i32 %79, i32* %gp_offset_p101, align 8, !dbg !230
  br label %vaarg.end110, !dbg !230

vaarg.in_mem106:                                  ; preds = %sw.default100
  %overflow_arg_area_p107 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %75, i32 0, i32 2, !dbg !231
  %overflow_arg_area108 = load i8*, i8** %overflow_arg_area_p107, align 8, !dbg !231
  %80 = bitcast i8* %overflow_arg_area108 to i8**, !dbg !231
  %overflow_arg_area.next109 = getelementptr i8, i8* %overflow_arg_area108, i32 8, !dbg !231
  store i8* %overflow_arg_area.next109, i8** %overflow_arg_area_p107, align 8, !dbg !231
  br label %vaarg.end110, !dbg !231

vaarg.end110:                                     ; preds = %vaarg.in_mem106, %vaarg.in_reg104
  %vaarg.addr111 = phi i8** [ %78, %vaarg.in_reg104 ], [ %80, %vaarg.in_mem106 ], !dbg !232
  %81 = load i8*, i8** %vaarg.addr111, align 8, !dbg !232
  store i8* %81, i8** %p2, align 8, !dbg !233
  %82 = load i8*, i8** %p2, align 8, !dbg !234
  %cmp112 = icmp eq i8* %82, null, !dbg !236
  br i1 %cmp112, label %if.then114, label %if.end115, !dbg !237

if.then114:                                       ; preds = %vaarg.end110
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.2, i32 0, i32 0), i8** %p2, align 8, !dbg !238
  br label %if.end115, !dbg !239

if.end115:                                        ; preds = %if.then114, %vaarg.end110
  %83 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !240
  %84 = load i8*, i8** %p2, align 8, !dbg !241
  %call116 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %83, i8* %84), !dbg !242
  br label %sw.epilog117, !dbg !243

sw.epilog117:                                     ; preds = %if.end115, %if.end99
  br label %sw.epilog203, !dbg !244

sw.bb118:                                         ; preds = %sw.epilog
  %85 = load %struct.__va_list_tag*, %struct.__va_list_tag** %ap.addr, align 8, !dbg !245
  %gp_offset_p119 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %85, i32 0, i32 0, !dbg !245
  %gp_offset120 = load i32, i32* %gp_offset_p119, align 8, !dbg !245
  %fits_in_gp121 = icmp ule i32 %gp_offset120, 40, !dbg !245
  br i1 %fits_in_gp121, label %vaarg.in_reg122, label %vaarg.in_mem124, !dbg !245

vaarg.in_reg122:                                  ; preds = %sw.bb118
  %86 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %85, i32 0, i32 3, !dbg !246
  %reg_save_area123 = load i8*, i8** %86, align 8, !dbg !246
  %87 = getelementptr i8, i8* %reg_save_area123, i32 %gp_offset120, !dbg !246
  %88 = bitcast i8* %87 to i32**, !dbg !246
  %89 = add i32 %gp_offset120, 8, !dbg !246
  store i32 %89, i32* %gp_offset_p119, align 8, !dbg !246
  br label %vaarg.end128, !dbg !246

vaarg.in_mem124:                                  ; preds = %sw.bb118
  %overflow_arg_area_p125 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %85, i32 0, i32 2, !dbg !247
  %overflow_arg_area126 = load i8*, i8** %overflow_arg_area_p125, align 8, !dbg !247
  %90 = bitcast i8* %overflow_arg_area126 to i32**, !dbg !247
  %overflow_arg_area.next127 = getelementptr i8, i8* %overflow_arg_area126, i32 8, !dbg !247
  store i8* %overflow_arg_area.next127, i8** %overflow_arg_area_p125, align 8, !dbg !247
  br label %vaarg.end128, !dbg !247

vaarg.end128:                                     ; preds = %vaarg.in_mem124, %vaarg.in_reg122
  %vaarg.addr129 = phi i32** [ %88, %vaarg.in_reg122 ], [ %90, %vaarg.in_mem124 ], !dbg !248
  %91 = load i32*, i32** %vaarg.addr129, align 8, !dbg !248
  store i32* %91, i32** %pw, align 8, !dbg !249
  %92 = load i32*, i32** %pw, align 8, !dbg !250
  %cmp130 = icmp eq i32* %92, null, !dbg !252
  br i1 %cmp130, label %if.then132, label %if.end133, !dbg !253

if.then132:                                       ; preds = %vaarg.end128
  store i32* getelementptr inbounds ([7 x i32], [7 x i32]* @.str.1, i32 0, i32 0), i32** %pw, align 8, !dbg !254
  br label %if.end133, !dbg !255

if.end133:                                        ; preds = %if.then132, %vaarg.end128
  %93 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !256
  %94 = load i32*, i32** %pw, align 8, !dbg !258
  %95 = load i32*, i32** %pw, align 8, !dbg !259
  %call134 = call i64 @wcslen(i32* %95) #8, !dbg !260
  %call135 = call i32 @archive_string_append_from_wcs(%struct.archive_string* %93, i32* %94, i64 %call134), !dbg !261
  %cmp136 = icmp ne i32 %call135, 0, !dbg !262
  br i1 %cmp136, label %land.lhs.true138, label %if.end143, !dbg !263

land.lhs.true138:                                 ; preds = %if.end133
  %call139 = call i32* @__errno_location() #1, !dbg !264
  %96 = load i32, i32* %call139, align 4, !dbg !264
  %cmp140 = icmp eq i32 %96, 12, !dbg !266
  br i1 %cmp140, label %if.then142, label %if.end143, !dbg !267

if.then142:                                       ; preds = %land.lhs.true138
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str, i32 0, i32 0)) #7, !dbg !268
  unreachable, !dbg !268

if.end143:                                        ; preds = %land.lhs.true138, %if.end133
  br label %sw.epilog203, !dbg !269

sw.bb144:                                         ; preds = %sw.epilog, %sw.epilog, %sw.epilog, %sw.epilog
  %97 = load i8, i8* %long_flag, align 1, !dbg !270
  %conv145 = sext i8 %97 to i32, !dbg !270
  switch i32 %conv145, label %sw.default182 [
    i32 106, label %sw.bb146
    i32 108, label %sw.bb158
    i32 122, label %sw.bb170
  ], !dbg !271

sw.bb146:                                         ; preds = %sw.bb144
  %98 = load %struct.__va_list_tag*, %struct.__va_list_tag** %ap.addr, align 8, !dbg !272
  %gp_offset_p147 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %98, i32 0, i32 0, !dbg !272
  %gp_offset148 = load i32, i32* %gp_offset_p147, align 8, !dbg !272
  %fits_in_gp149 = icmp ule i32 %gp_offset148, 40, !dbg !272
  br i1 %fits_in_gp149, label %vaarg.in_reg150, label %vaarg.in_mem152, !dbg !272

vaarg.in_reg150:                                  ; preds = %sw.bb146
  %99 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %98, i32 0, i32 3, !dbg !274
  %reg_save_area151 = load i8*, i8** %99, align 8, !dbg !274
  %100 = getelementptr i8, i8* %reg_save_area151, i32 %gp_offset148, !dbg !274
  %101 = bitcast i8* %100 to i64*, !dbg !274
  %102 = add i32 %gp_offset148, 8, !dbg !274
  store i32 %102, i32* %gp_offset_p147, align 8, !dbg !274
  br label %vaarg.end156, !dbg !274

vaarg.in_mem152:                                  ; preds = %sw.bb146
  %overflow_arg_area_p153 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %98, i32 0, i32 2, !dbg !276
  %overflow_arg_area154 = load i8*, i8** %overflow_arg_area_p153, align 8, !dbg !276
  %103 = bitcast i8* %overflow_arg_area154 to i64*, !dbg !276
  %overflow_arg_area.next155 = getelementptr i8, i8* %overflow_arg_area154, i32 8, !dbg !276
  store i8* %overflow_arg_area.next155, i8** %overflow_arg_area_p153, align 8, !dbg !276
  br label %vaarg.end156, !dbg !276

vaarg.end156:                                     ; preds = %vaarg.in_mem152, %vaarg.in_reg150
  %vaarg.addr157 = phi i64* [ %101, %vaarg.in_reg150 ], [ %103, %vaarg.in_mem152 ], !dbg !278
  %104 = load i64, i64* %vaarg.addr157, align 8, !dbg !278
  store i64 %104, i64* %u, align 8, !dbg !280
  br label %sw.epilog195, !dbg !281

sw.bb158:                                         ; preds = %sw.bb144
  %105 = load %struct.__va_list_tag*, %struct.__va_list_tag** %ap.addr, align 8, !dbg !282
  %gp_offset_p159 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %105, i32 0, i32 0, !dbg !282
  %gp_offset160 = load i32, i32* %gp_offset_p159, align 8, !dbg !282
  %fits_in_gp161 = icmp ule i32 %gp_offset160, 40, !dbg !282
  br i1 %fits_in_gp161, label %vaarg.in_reg162, label %vaarg.in_mem164, !dbg !282

vaarg.in_reg162:                                  ; preds = %sw.bb158
  %106 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %105, i32 0, i32 3, !dbg !283
  %reg_save_area163 = load i8*, i8** %106, align 8, !dbg !283
  %107 = getelementptr i8, i8* %reg_save_area163, i32 %gp_offset160, !dbg !283
  %108 = bitcast i8* %107 to i64*, !dbg !283
  %109 = add i32 %gp_offset160, 8, !dbg !283
  store i32 %109, i32* %gp_offset_p159, align 8, !dbg !283
  br label %vaarg.end168, !dbg !283

vaarg.in_mem164:                                  ; preds = %sw.bb158
  %overflow_arg_area_p165 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %105, i32 0, i32 2, !dbg !284
  %overflow_arg_area166 = load i8*, i8** %overflow_arg_area_p165, align 8, !dbg !284
  %110 = bitcast i8* %overflow_arg_area166 to i64*, !dbg !284
  %overflow_arg_area.next167 = getelementptr i8, i8* %overflow_arg_area166, i32 8, !dbg !284
  store i8* %overflow_arg_area.next167, i8** %overflow_arg_area_p165, align 8, !dbg !284
  br label %vaarg.end168, !dbg !284

vaarg.end168:                                     ; preds = %vaarg.in_mem164, %vaarg.in_reg162
  %vaarg.addr169 = phi i64* [ %108, %vaarg.in_reg162 ], [ %110, %vaarg.in_mem164 ], !dbg !285
  %111 = load i64, i64* %vaarg.addr169, align 8, !dbg !285
  store i64 %111, i64* %u, align 8, !dbg !286
  br label %sw.epilog195, !dbg !287

sw.bb170:                                         ; preds = %sw.bb144
  %112 = load %struct.__va_list_tag*, %struct.__va_list_tag** %ap.addr, align 8, !dbg !288
  %gp_offset_p171 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %112, i32 0, i32 0, !dbg !288
  %gp_offset172 = load i32, i32* %gp_offset_p171, align 8, !dbg !288
  %fits_in_gp173 = icmp ule i32 %gp_offset172, 40, !dbg !288
  br i1 %fits_in_gp173, label %vaarg.in_reg174, label %vaarg.in_mem176, !dbg !288

vaarg.in_reg174:                                  ; preds = %sw.bb170
  %113 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %112, i32 0, i32 3, !dbg !289
  %reg_save_area175 = load i8*, i8** %113, align 8, !dbg !289
  %114 = getelementptr i8, i8* %reg_save_area175, i32 %gp_offset172, !dbg !289
  %115 = bitcast i8* %114 to i64*, !dbg !289
  %116 = add i32 %gp_offset172, 8, !dbg !289
  store i32 %116, i32* %gp_offset_p171, align 8, !dbg !289
  br label %vaarg.end180, !dbg !289

vaarg.in_mem176:                                  ; preds = %sw.bb170
  %overflow_arg_area_p177 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %112, i32 0, i32 2, !dbg !290
  %overflow_arg_area178 = load i8*, i8** %overflow_arg_area_p177, align 8, !dbg !290
  %117 = bitcast i8* %overflow_arg_area178 to i64*, !dbg !290
  %overflow_arg_area.next179 = getelementptr i8, i8* %overflow_arg_area178, i32 8, !dbg !290
  store i8* %overflow_arg_area.next179, i8** %overflow_arg_area_p177, align 8, !dbg !290
  br label %vaarg.end180, !dbg !290

vaarg.end180:                                     ; preds = %vaarg.in_mem176, %vaarg.in_reg174
  %vaarg.addr181 = phi i64* [ %115, %vaarg.in_reg174 ], [ %117, %vaarg.in_mem176 ], !dbg !291
  %118 = load i64, i64* %vaarg.addr181, align 8, !dbg !291
  store i64 %118, i64* %u, align 8, !dbg !292
  br label %sw.epilog195, !dbg !293

sw.default182:                                    ; preds = %sw.bb144
  %119 = load %struct.__va_list_tag*, %struct.__va_list_tag** %ap.addr, align 8, !dbg !294
  %gp_offset_p183 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %119, i32 0, i32 0, !dbg !294
  %gp_offset184 = load i32, i32* %gp_offset_p183, align 8, !dbg !294
  %fits_in_gp185 = icmp ule i32 %gp_offset184, 40, !dbg !294
  br i1 %fits_in_gp185, label %vaarg.in_reg186, label %vaarg.in_mem188, !dbg !294

vaarg.in_reg186:                                  ; preds = %sw.default182
  %120 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %119, i32 0, i32 3, !dbg !295
  %reg_save_area187 = load i8*, i8** %120, align 8, !dbg !295
  %121 = getelementptr i8, i8* %reg_save_area187, i32 %gp_offset184, !dbg !295
  %122 = bitcast i8* %121 to i32*, !dbg !295
  %123 = add i32 %gp_offset184, 8, !dbg !295
  store i32 %123, i32* %gp_offset_p183, align 8, !dbg !295
  br label %vaarg.end192, !dbg !295

vaarg.in_mem188:                                  ; preds = %sw.default182
  %overflow_arg_area_p189 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %119, i32 0, i32 2, !dbg !296
  %overflow_arg_area190 = load i8*, i8** %overflow_arg_area_p189, align 8, !dbg !296
  %124 = bitcast i8* %overflow_arg_area190 to i32*, !dbg !296
  %overflow_arg_area.next191 = getelementptr i8, i8* %overflow_arg_area190, i32 8, !dbg !296
  store i8* %overflow_arg_area.next191, i8** %overflow_arg_area_p189, align 8, !dbg !296
  br label %vaarg.end192, !dbg !296

vaarg.end192:                                     ; preds = %vaarg.in_mem188, %vaarg.in_reg186
  %vaarg.addr193 = phi i32* [ %122, %vaarg.in_reg186 ], [ %124, %vaarg.in_mem188 ], !dbg !297
  %125 = load i32, i32* %vaarg.addr193, align 4, !dbg !297
  %conv194 = zext i32 %125 to i64, !dbg !297
  store i64 %conv194, i64* %u, align 8, !dbg !298
  br label %sw.epilog195, !dbg !299

sw.epilog195:                                     ; preds = %vaarg.end192, %vaarg.end180, %vaarg.end168, %vaarg.end156
  %126 = load i8*, i8** %p, align 8, !dbg !300
  %127 = load i8, i8* %126, align 1, !dbg !301
  %conv196 = sext i8 %127 to i32, !dbg !301
  switch i32 %conv196, label %sw.default199 [
    i32 111, label %sw.bb197
    i32 117, label %sw.bb198
  ], !dbg !302

sw.bb197:                                         ; preds = %sw.epilog195
  %128 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !303
  %129 = load i64, i64* %u, align 8, !dbg !305
  call void @append_uint(%struct.archive_string* %128, i64 %129, i32 8), !dbg !306
  br label %sw.epilog200, !dbg !307

sw.bb198:                                         ; preds = %sw.epilog195
  %130 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !308
  %131 = load i64, i64* %u, align 8, !dbg !309
  call void @append_uint(%struct.archive_string* %130, i64 %131, i32 10), !dbg !310
  br label %sw.epilog200, !dbg !311

sw.default199:                                    ; preds = %sw.epilog195
  %132 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !312
  %133 = load i64, i64* %u, align 8, !dbg !313
  call void @append_uint(%struct.archive_string* %132, i64 %133, i32 16), !dbg !314
  br label %sw.epilog200, !dbg !315

sw.epilog200:                                     ; preds = %sw.default199, %sw.bb198, %sw.bb197
  br label %sw.epilog203, !dbg !316

sw.default201:                                    ; preds = %sw.epilog
  %134 = load i8*, i8** %saved_p, align 8, !dbg !317
  store i8* %134, i8** %p, align 8, !dbg !318
  %135 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !319
  %136 = load i8*, i8** %p, align 8, !dbg !320
  %137 = load i8, i8* %136, align 1, !dbg !321
  %call202 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %135, i8 signext %137), !dbg !322
  br label %sw.epilog203, !dbg !323

sw.epilog203:                                     ; preds = %sw.default201, %sw.epilog200, %if.end143, %sw.epilog117, %sw.epilog72, %vaarg.end, %sw.bb16
  br label %for.inc, !dbg !324

for.inc:                                          ; preds = %sw.epilog203, %if.then10
  %138 = load i8*, i8** %p, align 8, !dbg !325
  %incdec.ptr204 = getelementptr inbounds i8, i8* %138, i32 1, !dbg !325
  store i8* %incdec.ptr204, i8** %p, align 8, !dbg !325
  br label %for.cond, !dbg !327

for.end:                                          ; preds = %if.then2, %for.cond
  ret void, !dbg !328
}

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #2

declare %struct.archive_string* @archive_string_ensure(%struct.archive_string*, i64) #3

; Function Attrs: noreturn
declare void @__archive_errx(i32, i8*) #4

declare %struct.archive_string* @archive_strappend_char(%struct.archive_string*, i8 signext) #3

; Function Attrs: nounwind uwtable
define internal void @append_int(%struct.archive_string* %as, i64 %d, i32 %base) #0 !dbg !36 {
entry:
  %as.addr = alloca %struct.archive_string*, align 8
  %d.addr = alloca i64, align 8
  %base.addr = alloca i32, align 4
  %ud = alloca i64, align 8
  store %struct.archive_string* %as, %struct.archive_string** %as.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %as.addr, metadata !329, metadata !50), !dbg !330
  store i64 %d, i64* %d.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %d.addr, metadata !331, metadata !50), !dbg !332
  store i32 %base, i32* %base.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %base.addr, metadata !333, metadata !50), !dbg !334
  call void @llvm.dbg.declare(metadata i64* %ud, metadata !335, metadata !50), !dbg !336
  %0 = load i64, i64* %d.addr, align 8, !dbg !337
  %cmp = icmp slt i64 %0, 0, !dbg !339
  br i1 %cmp, label %if.then, label %if.else, !dbg !340

if.then:                                          ; preds = %entry
  %1 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !341
  %call = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %1, i8 signext 45), !dbg !343
  %2 = load i64, i64* %d.addr, align 8, !dbg !344
  %cmp1 = icmp eq i64 %2, -9223372036854775808, !dbg !345
  br i1 %cmp1, label %cond.true, label %cond.false, !dbg !346

cond.true:                                        ; preds = %if.then
  br label %cond.end, !dbg !347

cond.false:                                       ; preds = %if.then
  %3 = load i64, i64* %d.addr, align 8, !dbg !349
  %sub = sub nsw i64 0, %3, !dbg !351
  br label %cond.end, !dbg !352

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ -9223372036854775808, %cond.true ], [ %sub, %cond.false ], !dbg !353
  store i64 %cond, i64* %ud, align 8, !dbg !355
  br label %if.end, !dbg !356

if.else:                                          ; preds = %entry
  %4 = load i64, i64* %d.addr, align 8, !dbg !357
  store i64 %4, i64* %ud, align 8, !dbg !358
  br label %if.end

if.end:                                           ; preds = %if.else, %cond.end
  %5 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !359
  %6 = load i64, i64* %ud, align 8, !dbg !360
  %7 = load i32, i32* %base.addr, align 4, !dbg !361
  call void @append_uint(%struct.archive_string* %5, i64 %6, i32 %7), !dbg !362
  ret void, !dbg !363
}

declare i32 @archive_string_append_from_wcs(%struct.archive_string*, i32*, i64) #3

; Function Attrs: nounwind readonly
declare i64 @wcslen(i32*) #5

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #6

declare %struct.archive_string* @archive_strcat(%struct.archive_string*, i8*) #3

; Function Attrs: nounwind uwtable
define internal void @append_uint(%struct.archive_string* %as, i64 %d, i32 %base) #0 !dbg !41 {
entry:
  %as.addr = alloca %struct.archive_string*, align 8
  %d.addr = alloca i64, align 8
  %base.addr = alloca i32, align 4
  store %struct.archive_string* %as, %struct.archive_string** %as.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %as.addr, metadata !364, metadata !50), !dbg !365
  store i64 %d, i64* %d.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %d.addr, metadata !366, metadata !50), !dbg !367
  store i32 %base, i32* %base.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %base.addr, metadata !368, metadata !50), !dbg !369
  %0 = load i64, i64* %d.addr, align 8, !dbg !370
  %1 = load i32, i32* %base.addr, align 4, !dbg !372
  %conv = zext i32 %1 to i64, !dbg !372
  %cmp = icmp uge i64 %0, %conv, !dbg !373
  br i1 %cmp, label %if.then, label %if.end, !dbg !374

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !375
  %3 = load i64, i64* %d.addr, align 8, !dbg !376
  %4 = load i32, i32* %base.addr, align 4, !dbg !377
  %conv2 = zext i32 %4 to i64, !dbg !377
  %div = udiv i64 %3, %conv2, !dbg !378
  %5 = load i32, i32* %base.addr, align 4, !dbg !379
  call void @append_uint(%struct.archive_string* %2, i64 %div, i32 %5), !dbg !380
  br label %if.end, !dbg !380

if.end:                                           ; preds = %if.then, %entry
  %6 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !381
  %7 = load i64, i64* %d.addr, align 8, !dbg !382
  %8 = load i32, i32* %base.addr, align 4, !dbg !383
  %conv3 = zext i32 %8 to i64, !dbg !383
  %rem = urem i64 %7, %conv3, !dbg !384
  %9 = load i8*, i8** @append_uint.digits, align 8, !dbg !385
  %arrayidx = getelementptr inbounds i8, i8* %9, i64 %rem, !dbg !385
  %10 = load i8, i8* %arrayidx, align 1, !dbg !385
  %call = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %6, i8 signext %10), !dbg !386
  ret void, !dbg !387
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noreturn "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { noreturn }
attributes #8 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!46, !47}
!llvm.ident = !{!48}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !9, globals: !44)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string_sprintf.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !5, !6}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!6 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintmax_t", file: !7, line: 135, baseType: !8)
!7 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!8 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!9 = !{!10, !25, !36, !41}
!10 = distinct !DISubprogram(name: "archive_string_sprintf", scope: !1, file: !1, line: 77, type: !11, isLocal: false, isDefinition: true, scopeLine: 78, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!11 = !DISubroutineType(types: !12)
!12 = !{null, !13, !23, null}
!13 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !14, size: 64, align: 64)
!14 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !15, line: 58, size: 192, align: 64, elements: !16)
!15 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!16 = !{!17, !19, !22}
!17 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !14, file: !15, line: 59, baseType: !18, size: 64, align: 64)
!18 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!19 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !14, file: !15, line: 60, baseType: !20, size: 64, align: 64, offset: 64)
!20 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !21, line: 62, baseType: !8)
!21 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!22 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !14, file: !15, line: 61, baseType: !20, size: 64, align: 64, offset: 128)
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64, align: 64)
!24 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !5)
!25 = distinct !DISubprogram(name: "archive_string_vsprintf", scope: !1, file: !1, line: 91, type: !26, isLocal: false, isDefinition: true, scopeLine: 93, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!26 = !DISubroutineType(types: !27)
!27 = !{null, !13, !23, !28}
!28 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !29, size: 64, align: 64)
!29 = !DICompositeType(tag: DW_TAG_structure_type, name: "__va_list_tag", file: !1, line: 79, size: 192, align: 64, elements: !30)
!30 = !{!31, !33, !34, !35}
!31 = !DIDerivedType(tag: DW_TAG_member, name: "gp_offset", scope: !29, file: !1, line: 79, baseType: !32, size: 32, align: 32)
!32 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "fp_offset", scope: !29, file: !1, line: 79, baseType: !32, size: 32, align: 32, offset: 32)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "overflow_arg_area", scope: !29, file: !1, line: 79, baseType: !4, size: 64, align: 64, offset: 64)
!35 = !DIDerivedType(tag: DW_TAG_member, name: "reg_save_area", scope: !29, file: !1, line: 79, baseType: !4, size: 64, align: 64, offset: 128)
!36 = distinct !DISubprogram(name: "append_int", scope: !1, file: !1, line: 63, type: !37, isLocal: true, isDefinition: true, scopeLine: 64, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!37 = !DISubroutineType(types: !38)
!38 = !{null, !13, !39, !32}
!39 = !DIDerivedType(tag: DW_TAG_typedef, name: "intmax_t", file: !7, line: 134, baseType: !40)
!40 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!41 = distinct !DISubprogram(name: "append_uint", scope: !1, file: !1, line: 54, type: !42, isLocal: true, isDefinition: true, scopeLine: 55, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!42 = !DISubroutineType(types: !43)
!43 = !{null, !13, !6, !32}
!44 = !{!45}
!45 = !DIGlobalVariable(name: "digits", scope: !41, file: !1, line: 56, type: !23, isLocal: true, isDefinition: true, variable: i8** @append_uint.digits)
!46 = !{i32 2, !"Dwarf Version", i32 4}
!47 = !{i32 2, !"Debug Info Version", i32 3}
!48 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!49 = !DILocalVariable(name: "as", arg: 1, scope: !10, file: !1, line: 77, type: !13)
!50 = !DIExpression()
!51 = !DILocation(line: 77, column: 47, scope: !10)
!52 = !DILocalVariable(name: "fmt", arg: 2, scope: !10, file: !1, line: 77, type: !23)
!53 = !DILocation(line: 77, column: 63, scope: !10)
!54 = !DILocalVariable(name: "ap", scope: !10, file: !1, line: 79, type: !55)
!55 = !DIDerivedType(tag: DW_TAG_typedef, name: "va_list", file: !56, line: 79, baseType: !57)
!56 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!57 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gnuc_va_list", file: !58, line: 50, baseType: !59)
!58 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stdarg.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!59 = !DIDerivedType(tag: DW_TAG_typedef, name: "__builtin_va_list", file: !1, line: 79, baseType: !60)
!60 = !DICompositeType(tag: DW_TAG_array_type, baseType: !29, size: 192, align: 64, elements: !61)
!61 = !{!62}
!62 = !DISubrange(count: 1)
!63 = !DILocation(line: 79, column: 10, scope: !10)
!64 = !DILocation(line: 81, column: 2, scope: !10)
!65 = !DILocation(line: 82, column: 26, scope: !10)
!66 = !DILocation(line: 82, column: 30, scope: !10)
!67 = !DILocation(line: 82, column: 35, scope: !10)
!68 = !DILocation(line: 82, column: 2, scope: !10)
!69 = !DILocation(line: 83, column: 2, scope: !10)
!70 = !DILocation(line: 84, column: 1, scope: !10)
!71 = !DILocalVariable(name: "as", arg: 1, scope: !25, file: !1, line: 91, type: !13)
!72 = !DILocation(line: 91, column: 48, scope: !25)
!73 = !DILocalVariable(name: "fmt", arg: 2, scope: !25, file: !1, line: 91, type: !23)
!74 = !DILocation(line: 91, column: 64, scope: !25)
!75 = !DILocalVariable(name: "ap", arg: 3, scope: !25, file: !1, line: 92, type: !28)
!76 = !DILocation(line: 92, column: 13, scope: !25)
!77 = !DILocalVariable(name: "long_flag", scope: !25, file: !1, line: 94, type: !5)
!78 = !DILocation(line: 94, column: 7, scope: !25)
!79 = !DILocalVariable(name: "s", scope: !25, file: !1, line: 95, type: !39)
!80 = !DILocation(line: 95, column: 11, scope: !25)
!81 = !DILocalVariable(name: "u", scope: !25, file: !1, line: 96, type: !6)
!82 = !DILocation(line: 96, column: 12, scope: !25)
!83 = !DILocalVariable(name: "p", scope: !25, file: !1, line: 97, type: !23)
!84 = !DILocation(line: 97, column: 14, scope: !25)
!85 = !DILocalVariable(name: "p2", scope: !25, file: !1, line: 97, type: !23)
!86 = !DILocation(line: 97, column: 18, scope: !25)
!87 = !DILocalVariable(name: "pw", scope: !25, file: !1, line: 98, type: !88)
!88 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !89, size: 64, align: 64)
!89 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !90)
!90 = !DIDerivedType(tag: DW_TAG_typedef, name: "wchar_t", file: !21, line: 90, baseType: !91)
!91 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!92 = !DILocation(line: 98, column: 17, scope: !25)
!93 = !DILocation(line: 100, column: 28, scope: !94)
!94 = distinct !DILexicalBlock(scope: !25, file: !1, line: 100, column: 6)
!95 = !DILocation(line: 100, column: 6, scope: !94)
!96 = !DILocation(line: 100, column: 36, scope: !94)
!97 = !DILocation(line: 100, column: 6, scope: !25)
!98 = !DILocation(line: 101, column: 3, scope: !94)
!99 = !DILocation(line: 103, column: 6, scope: !100)
!100 = distinct !DILexicalBlock(scope: !25, file: !1, line: 103, column: 6)
!101 = !DILocation(line: 103, column: 10, scope: !100)
!102 = !DILocation(line: 103, column: 6, scope: !25)
!103 = !DILocation(line: 104, column: 3, scope: !104)
!104 = distinct !DILexicalBlock(scope: !100, file: !1, line: 103, column: 19)
!105 = !DILocation(line: 104, column: 7, scope: !104)
!106 = !DILocation(line: 104, column: 12, scope: !104)
!107 = !DILocation(line: 105, column: 3, scope: !104)
!108 = !DILocation(line: 108, column: 11, scope: !109)
!109 = distinct !DILexicalBlock(scope: !25, file: !1, line: 108, column: 2)
!110 = !DILocation(line: 108, column: 9, scope: !109)
!111 = !DILocation(line: 108, column: 7, scope: !109)
!112 = !DILocation(line: 108, column: 17, scope: !113)
!113 = !DILexicalBlockFile(scope: !114, file: !1, discriminator: 1)
!114 = distinct !DILexicalBlock(scope: !109, file: !1, line: 108, column: 2)
!115 = !DILocation(line: 108, column: 16, scope: !113)
!116 = !DILocation(line: 108, column: 19, scope: !113)
!117 = !DILocation(line: 108, column: 2, scope: !113)
!118 = !DILocalVariable(name: "saved_p", scope: !119, file: !1, line: 109, type: !23)
!119 = distinct !DILexicalBlock(scope: !114, file: !1, line: 108, column: 33)
!120 = !DILocation(line: 109, column: 15, scope: !119)
!121 = !DILocation(line: 109, column: 25, scope: !119)
!122 = !DILocation(line: 111, column: 8, scope: !123)
!123 = distinct !DILexicalBlock(scope: !119, file: !1, line: 111, column: 7)
!124 = !DILocation(line: 111, column: 7, scope: !123)
!125 = !DILocation(line: 111, column: 10, scope: !123)
!126 = !DILocation(line: 111, column: 7, scope: !119)
!127 = !DILocation(line: 112, column: 27, scope: !128)
!128 = distinct !DILexicalBlock(scope: !123, file: !1, line: 111, column: 18)
!129 = !DILocation(line: 112, column: 32, scope: !128)
!130 = !DILocation(line: 112, column: 31, scope: !128)
!131 = !DILocation(line: 112, column: 4, scope: !128)
!132 = !DILocation(line: 113, column: 4, scope: !128)
!133 = !DILocation(line: 116, column: 4, scope: !119)
!134 = !DILocation(line: 118, column: 13, scope: !119)
!135 = !DILocation(line: 119, column: 11, scope: !119)
!136 = !DILocation(line: 119, column: 10, scope: !119)
!137 = !DILocation(line: 119, column: 3, scope: !119)
!138 = !DILocation(line: 123, column: 17, scope: !139)
!139 = distinct !DILexicalBlock(scope: !119, file: !1, line: 119, column: 14)
!140 = !DILocation(line: 123, column: 16, scope: !139)
!141 = !DILocation(line: 123, column: 14, scope: !139)
!142 = !DILocation(line: 124, column: 5, scope: !139)
!143 = !DILocation(line: 125, column: 4, scope: !139)
!144 = !DILocation(line: 128, column: 12, scope: !119)
!145 = !DILocation(line: 128, column: 11, scope: !119)
!146 = !DILocation(line: 128, column: 3, scope: !119)
!147 = !DILocation(line: 130, column: 27, scope: !148)
!148 = distinct !DILexicalBlock(scope: !119, file: !1, line: 128, column: 15)
!149 = !DILocation(line: 130, column: 4, scope: !148)
!150 = !DILocation(line: 131, column: 4, scope: !148)
!151 = !DILocation(line: 133, column: 8, scope: !148)
!152 = !DILocation(line: 133, column: 8, scope: !153)
!153 = !DILexicalBlockFile(scope: !148, file: !1, discriminator: 1)
!154 = !DILocation(line: 133, column: 8, scope: !155)
!155 = !DILexicalBlockFile(scope: !148, file: !1, discriminator: 2)
!156 = !DILocation(line: 133, column: 8, scope: !157)
!157 = !DILexicalBlockFile(scope: !148, file: !1, discriminator: 3)
!158 = !DILocation(line: 133, column: 6, scope: !157)
!159 = !DILocation(line: 134, column: 27, scope: !148)
!160 = !DILocation(line: 134, column: 37, scope: !148)
!161 = !DILocation(line: 134, column: 31, scope: !148)
!162 = !DILocation(line: 134, column: 4, scope: !148)
!163 = !DILocation(line: 135, column: 4, scope: !148)
!164 = !DILocation(line: 137, column: 11, scope: !148)
!165 = !DILocation(line: 137, column: 4, scope: !148)
!166 = !DILocation(line: 138, column: 18, scope: !167)
!167 = distinct !DILexicalBlock(scope: !148, file: !1, line: 137, column: 22)
!168 = !DILocation(line: 138, column: 18, scope: !169)
!169 = !DILexicalBlockFile(scope: !167, file: !1, discriminator: 1)
!170 = !DILocation(line: 138, column: 18, scope: !171)
!171 = !DILexicalBlockFile(scope: !167, file: !1, discriminator: 2)
!172 = !DILocation(line: 138, column: 18, scope: !173)
!173 = !DILexicalBlockFile(scope: !167, file: !1, discriminator: 3)
!174 = !DILocation(line: 138, column: 16, scope: !173)
!175 = !DILocation(line: 138, column: 40, scope: !173)
!176 = !DILocation(line: 139, column: 18, scope: !167)
!177 = !DILocation(line: 139, column: 18, scope: !169)
!178 = !DILocation(line: 139, column: 18, scope: !171)
!179 = !DILocation(line: 139, column: 18, scope: !173)
!180 = !DILocation(line: 139, column: 16, scope: !173)
!181 = !DILocation(line: 139, column: 36, scope: !173)
!182 = !DILocation(line: 140, column: 18, scope: !167)
!183 = !DILocation(line: 140, column: 18, scope: !169)
!184 = !DILocation(line: 140, column: 18, scope: !171)
!185 = !DILocation(line: 140, column: 18, scope: !173)
!186 = !DILocation(line: 140, column: 16, scope: !173)
!187 = !DILocation(line: 140, column: 39, scope: !173)
!188 = !DILocation(line: 141, column: 18, scope: !167)
!189 = !DILocation(line: 141, column: 18, scope: !169)
!190 = !DILocation(line: 141, column: 18, scope: !171)
!191 = !DILocation(line: 141, column: 18, scope: !173)
!192 = !DILocation(line: 141, column: 16, scope: !173)
!193 = !DILocation(line: 141, column: 35, scope: !173)
!194 = !DILocation(line: 143, column: 22, scope: !148)
!195 = !DILocation(line: 143, column: 26, scope: !148)
!196 = !DILocation(line: 143, column: 11, scope: !148)
!197 = !DILocation(line: 144, column: 4, scope: !148)
!198 = !DILocation(line: 146, column: 11, scope: !148)
!199 = !DILocation(line: 146, column: 4, scope: !148)
!200 = !DILocation(line: 148, column: 10, scope: !201)
!201 = distinct !DILexicalBlock(scope: !148, file: !1, line: 146, column: 22)
!202 = !DILocation(line: 148, column: 10, scope: !203)
!203 = !DILexicalBlockFile(scope: !201, file: !1, discriminator: 1)
!204 = !DILocation(line: 148, column: 10, scope: !205)
!205 = !DILexicalBlockFile(scope: !201, file: !1, discriminator: 2)
!206 = !DILocation(line: 148, column: 10, scope: !207)
!207 = !DILexicalBlockFile(scope: !201, file: !1, discriminator: 3)
!208 = !DILocation(line: 148, column: 8, scope: !207)
!209 = !DILocation(line: 149, column: 9, scope: !210)
!210 = distinct !DILexicalBlock(scope: !201, file: !1, line: 149, column: 9)
!211 = !DILocation(line: 149, column: 12, scope: !210)
!212 = !DILocation(line: 149, column: 9, scope: !201)
!213 = !DILocation(line: 150, column: 9, scope: !210)
!214 = !DILocation(line: 150, column: 6, scope: !210)
!215 = !DILocation(line: 151, column: 40, scope: !216)
!216 = distinct !DILexicalBlock(scope: !201, file: !1, line: 151, column: 9)
!217 = !DILocation(line: 151, column: 44, scope: !216)
!218 = !DILocation(line: 152, column: 16, scope: !216)
!219 = !DILocation(line: 152, column: 9, scope: !216)
!220 = !DILocation(line: 151, column: 9, scope: !216)
!221 = !DILocation(line: 152, column: 21, scope: !216)
!222 = !DILocation(line: 152, column: 26, scope: !216)
!223 = !DILocation(line: 152, column: 29, scope: !224)
!224 = !DILexicalBlockFile(scope: !216, file: !1, discriminator: 1)
!225 = !DILocation(line: 152, column: 35, scope: !224)
!226 = !DILocation(line: 151, column: 9, scope: !203)
!227 = !DILocation(line: 153, column: 6, scope: !216)
!228 = !DILocation(line: 154, column: 5, scope: !201)
!229 = !DILocation(line: 156, column: 10, scope: !201)
!230 = !DILocation(line: 156, column: 10, scope: !203)
!231 = !DILocation(line: 156, column: 10, scope: !205)
!232 = !DILocation(line: 156, column: 10, scope: !207)
!233 = !DILocation(line: 156, column: 8, scope: !207)
!234 = !DILocation(line: 157, column: 9, scope: !235)
!235 = distinct !DILexicalBlock(scope: !201, file: !1, line: 157, column: 9)
!236 = !DILocation(line: 157, column: 12, scope: !235)
!237 = !DILocation(line: 157, column: 9, scope: !201)
!238 = !DILocation(line: 158, column: 9, scope: !235)
!239 = !DILocation(line: 158, column: 6, scope: !235)
!240 = !DILocation(line: 159, column: 20, scope: !201)
!241 = !DILocation(line: 159, column: 24, scope: !201)
!242 = !DILocation(line: 159, column: 5, scope: !201)
!243 = !DILocation(line: 160, column: 5, scope: !201)
!244 = !DILocation(line: 162, column: 4, scope: !148)
!245 = !DILocation(line: 164, column: 9, scope: !148)
!246 = !DILocation(line: 164, column: 9, scope: !153)
!247 = !DILocation(line: 164, column: 9, scope: !155)
!248 = !DILocation(line: 164, column: 9, scope: !157)
!249 = !DILocation(line: 164, column: 7, scope: !157)
!250 = !DILocation(line: 165, column: 8, scope: !251)
!251 = distinct !DILexicalBlock(scope: !148, file: !1, line: 165, column: 8)
!252 = !DILocation(line: 165, column: 11, scope: !251)
!253 = !DILocation(line: 165, column: 8, scope: !148)
!254 = !DILocation(line: 166, column: 8, scope: !251)
!255 = !DILocation(line: 166, column: 5, scope: !251)
!256 = !DILocation(line: 167, column: 39, scope: !257)
!257 = distinct !DILexicalBlock(scope: !148, file: !1, line: 167, column: 8)
!258 = !DILocation(line: 167, column: 43, scope: !257)
!259 = !DILocation(line: 168, column: 15, scope: !257)
!260 = !DILocation(line: 168, column: 8, scope: !257)
!261 = !DILocation(line: 167, column: 8, scope: !257)
!262 = !DILocation(line: 168, column: 20, scope: !257)
!263 = !DILocation(line: 168, column: 25, scope: !257)
!264 = !DILocation(line: 168, column: 28, scope: !265)
!265 = !DILexicalBlockFile(scope: !257, file: !1, discriminator: 1)
!266 = !DILocation(line: 168, column: 34, scope: !265)
!267 = !DILocation(line: 167, column: 8, scope: !153)
!268 = !DILocation(line: 169, column: 5, scope: !257)
!269 = !DILocation(line: 170, column: 4, scope: !148)
!270 = !DILocation(line: 173, column: 11, scope: !148)
!271 = !DILocation(line: 173, column: 4, scope: !148)
!272 = !DILocation(line: 174, column: 18, scope: !273)
!273 = distinct !DILexicalBlock(scope: !148, file: !1, line: 173, column: 22)
!274 = !DILocation(line: 174, column: 18, scope: !275)
!275 = !DILexicalBlockFile(scope: !273, file: !1, discriminator: 1)
!276 = !DILocation(line: 174, column: 18, scope: !277)
!277 = !DILexicalBlockFile(scope: !273, file: !1, discriminator: 2)
!278 = !DILocation(line: 174, column: 18, scope: !279)
!279 = !DILexicalBlockFile(scope: !273, file: !1, discriminator: 3)
!280 = !DILocation(line: 174, column: 16, scope: !279)
!281 = !DILocation(line: 174, column: 41, scope: !279)
!282 = !DILocation(line: 175, column: 18, scope: !273)
!283 = !DILocation(line: 175, column: 18, scope: !275)
!284 = !DILocation(line: 175, column: 18, scope: !277)
!285 = !DILocation(line: 175, column: 18, scope: !279)
!286 = !DILocation(line: 175, column: 16, scope: !279)
!287 = !DILocation(line: 175, column: 45, scope: !279)
!288 = !DILocation(line: 176, column: 18, scope: !273)
!289 = !DILocation(line: 176, column: 18, scope: !275)
!290 = !DILocation(line: 176, column: 18, scope: !277)
!291 = !DILocation(line: 176, column: 18, scope: !279)
!292 = !DILocation(line: 176, column: 16, scope: !279)
!293 = !DILocation(line: 176, column: 38, scope: !279)
!294 = !DILocation(line: 177, column: 18, scope: !273)
!295 = !DILocation(line: 177, column: 18, scope: !275)
!296 = !DILocation(line: 177, column: 18, scope: !277)
!297 = !DILocation(line: 177, column: 18, scope: !279)
!298 = !DILocation(line: 177, column: 16, scope: !279)
!299 = !DILocation(line: 177, column: 44, scope: !279)
!300 = !DILocation(line: 180, column: 13, scope: !148)
!301 = !DILocation(line: 180, column: 12, scope: !148)
!302 = !DILocation(line: 180, column: 4, scope: !148)
!303 = !DILocation(line: 181, column: 26, scope: !304)
!304 = distinct !DILexicalBlock(scope: !148, file: !1, line: 180, column: 16)
!305 = !DILocation(line: 181, column: 30, scope: !304)
!306 = !DILocation(line: 181, column: 14, scope: !304)
!307 = !DILocation(line: 181, column: 37, scope: !304)
!308 = !DILocation(line: 182, column: 26, scope: !304)
!309 = !DILocation(line: 182, column: 30, scope: !304)
!310 = !DILocation(line: 182, column: 14, scope: !304)
!311 = !DILocation(line: 182, column: 38, scope: !304)
!312 = !DILocation(line: 183, column: 25, scope: !304)
!313 = !DILocation(line: 183, column: 29, scope: !304)
!314 = !DILocation(line: 183, column: 13, scope: !304)
!315 = !DILocation(line: 183, column: 37, scope: !304)
!316 = !DILocation(line: 185, column: 4, scope: !148)
!317 = !DILocation(line: 188, column: 8, scope: !148)
!318 = !DILocation(line: 188, column: 6, scope: !148)
!319 = !DILocation(line: 189, column: 27, scope: !148)
!320 = !DILocation(line: 189, column: 32, scope: !148)
!321 = !DILocation(line: 189, column: 31, scope: !148)
!322 = !DILocation(line: 189, column: 4, scope: !148)
!323 = !DILocation(line: 190, column: 3, scope: !148)
!324 = !DILocation(line: 191, column: 2, scope: !119)
!325 = !DILocation(line: 108, column: 29, scope: !326)
!326 = !DILexicalBlockFile(scope: !114, file: !1, discriminator: 2)
!327 = !DILocation(line: 108, column: 2, scope: !326)
!328 = !DILocation(line: 192, column: 1, scope: !25)
!329 = !DILocalVariable(name: "as", arg: 1, scope: !36, file: !1, line: 63, type: !13)
!330 = !DILocation(line: 63, column: 35, scope: !36)
!331 = !DILocalVariable(name: "d", arg: 2, scope: !36, file: !1, line: 63, type: !39)
!332 = !DILocation(line: 63, column: 48, scope: !36)
!333 = !DILocalVariable(name: "base", arg: 3, scope: !36, file: !1, line: 63, type: !32)
!334 = !DILocation(line: 63, column: 60, scope: !36)
!335 = !DILocalVariable(name: "ud", scope: !36, file: !1, line: 65, type: !6)
!336 = !DILocation(line: 65, column: 12, scope: !36)
!337 = !DILocation(line: 67, column: 6, scope: !338)
!338 = distinct !DILexicalBlock(scope: !36, file: !1, line: 67, column: 6)
!339 = !DILocation(line: 67, column: 8, scope: !338)
!340 = !DILocation(line: 67, column: 6, scope: !36)
!341 = !DILocation(line: 68, column: 26, scope: !342)
!342 = distinct !DILexicalBlock(scope: !338, file: !1, line: 67, column: 13)
!343 = !DILocation(line: 68, column: 3, scope: !342)
!344 = !DILocation(line: 69, column: 9, scope: !342)
!345 = !DILocation(line: 69, column: 11, scope: !342)
!346 = !DILocation(line: 69, column: 8, scope: !342)
!347 = !DILocation(line: 69, column: 8, scope: !348)
!348 = !DILexicalBlockFile(scope: !342, file: !1, discriminator: 1)
!349 = !DILocation(line: 69, column: 71, scope: !350)
!350 = !DILexicalBlockFile(scope: !342, file: !1, discriminator: 2)
!351 = !DILocation(line: 69, column: 70, scope: !350)
!352 = !DILocation(line: 69, column: 8, scope: !350)
!353 = !DILocation(line: 69, column: 8, scope: !354)
!354 = !DILexicalBlockFile(scope: !342, file: !1, discriminator: 3)
!355 = !DILocation(line: 69, column: 6, scope: !354)
!356 = !DILocation(line: 70, column: 2, scope: !342)
!357 = !DILocation(line: 71, column: 8, scope: !338)
!358 = !DILocation(line: 71, column: 6, scope: !338)
!359 = !DILocation(line: 72, column: 14, scope: !36)
!360 = !DILocation(line: 72, column: 18, scope: !36)
!361 = !DILocation(line: 72, column: 22, scope: !36)
!362 = !DILocation(line: 72, column: 2, scope: !36)
!363 = !DILocation(line: 73, column: 1, scope: !36)
!364 = !DILocalVariable(name: "as", arg: 1, scope: !41, file: !1, line: 54, type: !13)
!365 = !DILocation(line: 54, column: 36, scope: !41)
!366 = !DILocalVariable(name: "d", arg: 2, scope: !41, file: !1, line: 54, type: !6)
!367 = !DILocation(line: 54, column: 50, scope: !41)
!368 = !DILocalVariable(name: "base", arg: 3, scope: !41, file: !1, line: 54, type: !32)
!369 = !DILocation(line: 54, column: 62, scope: !41)
!370 = !DILocation(line: 57, column: 6, scope: !371)
!371 = distinct !DILexicalBlock(scope: !41, file: !1, line: 57, column: 6)
!372 = !DILocation(line: 57, column: 11, scope: !371)
!373 = !DILocation(line: 57, column: 8, scope: !371)
!374 = !DILocation(line: 57, column: 6, scope: !41)
!375 = !DILocation(line: 58, column: 15, scope: !371)
!376 = !DILocation(line: 58, column: 19, scope: !371)
!377 = !DILocation(line: 58, column: 21, scope: !371)
!378 = !DILocation(line: 58, column: 20, scope: !371)
!379 = !DILocation(line: 58, column: 27, scope: !371)
!380 = !DILocation(line: 58, column: 3, scope: !371)
!381 = !DILocation(line: 59, column: 25, scope: !41)
!382 = !DILocation(line: 59, column: 36, scope: !41)
!383 = !DILocation(line: 59, column: 40, scope: !41)
!384 = !DILocation(line: 59, column: 38, scope: !41)
!385 = !DILocation(line: 59, column: 29, scope: !41)
!386 = !DILocation(line: 59, column: 2, scope: !41)
!387 = !DILocation(line: 60, column: 1, scope: !41)
