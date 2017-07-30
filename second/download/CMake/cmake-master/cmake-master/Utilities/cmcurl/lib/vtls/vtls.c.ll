; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/vtls/vtls.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.ssl_primary_config = type { i64, i64, i8, i8, i8, i8*, i8*, i8*, i8*, i8*, i8*, i8 }

@Curl_cstrdup = external global i8* (i8*)*, align 8
@Curl_cfree = external global void (i8*)*, align 8

; Function Attrs: nounwind uwtable
define zeroext i1 @Curl_ssl_config_matches(%struct.ssl_primary_config* %data, %struct.ssl_primary_config* %needle) #0 !dbg !21 {
entry:
  %retval = alloca i1, align 1
  %data.addr = alloca %struct.ssl_primary_config*, align 8
  %needle.addr = alloca %struct.ssl_primary_config*, align 8
  store %struct.ssl_primary_config* %data, %struct.ssl_primary_config** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.ssl_primary_config** %data.addr, metadata !54, metadata !55), !dbg !56
  store %struct.ssl_primary_config* %needle, %struct.ssl_primary_config** %needle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.ssl_primary_config** %needle.addr, metadata !57, metadata !55), !dbg !58
  %0 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %data.addr, align 8, !dbg !59
  %version = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %0, i32 0, i32 0, !dbg !61
  %1 = load i64, i64* %version, align 8, !dbg !61
  %2 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %needle.addr, align 8, !dbg !62
  %version1 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %2, i32 0, i32 0, !dbg !63
  %3 = load i64, i64* %version1, align 8, !dbg !63
  %cmp = icmp eq i64 %1, %3, !dbg !64
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !65

land.lhs.true:                                    ; preds = %entry
  %4 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %data.addr, align 8, !dbg !66
  %version_max = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %4, i32 0, i32 1, !dbg !67
  %5 = load i64, i64* %version_max, align 8, !dbg !67
  %6 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %needle.addr, align 8, !dbg !68
  %version_max2 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %6, i32 0, i32 1, !dbg !69
  %7 = load i64, i64* %version_max2, align 8, !dbg !69
  %cmp3 = icmp eq i64 %5, %7, !dbg !70
  br i1 %cmp3, label %land.lhs.true4, label %if.end, !dbg !71

land.lhs.true4:                                   ; preds = %land.lhs.true
  %8 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %data.addr, align 8, !dbg !72
  %verifypeer = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %8, i32 0, i32 2, !dbg !73
  %9 = load i8, i8* %verifypeer, align 8, !dbg !73
  %tobool = trunc i8 %9 to i1, !dbg !73
  %conv = zext i1 %tobool to i32, !dbg !72
  %10 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %needle.addr, align 8, !dbg !74
  %verifypeer5 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %10, i32 0, i32 2, !dbg !75
  %11 = load i8, i8* %verifypeer5, align 8, !dbg !75
  %tobool6 = trunc i8 %11 to i1, !dbg !75
  %conv7 = zext i1 %tobool6 to i32, !dbg !74
  %cmp8 = icmp eq i32 %conv, %conv7, !dbg !76
  br i1 %cmp8, label %land.lhs.true10, label %if.end, !dbg !77

land.lhs.true10:                                  ; preds = %land.lhs.true4
  %12 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %data.addr, align 8, !dbg !78
  %verifyhost = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %12, i32 0, i32 3, !dbg !79
  %13 = load i8, i8* %verifyhost, align 1, !dbg !79
  %tobool11 = trunc i8 %13 to i1, !dbg !79
  %conv12 = zext i1 %tobool11 to i32, !dbg !78
  %14 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %needle.addr, align 8, !dbg !80
  %verifyhost13 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %14, i32 0, i32 3, !dbg !81
  %15 = load i8, i8* %verifyhost13, align 1, !dbg !81
  %tobool14 = trunc i8 %15 to i1, !dbg !81
  %conv15 = zext i1 %tobool14 to i32, !dbg !80
  %cmp16 = icmp eq i32 %conv12, %conv15, !dbg !82
  br i1 %cmp16, label %land.lhs.true18, label %if.end, !dbg !83

land.lhs.true18:                                  ; preds = %land.lhs.true10
  %16 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %data.addr, align 8, !dbg !84
  %CApath = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %16, i32 0, i32 5, !dbg !85
  %17 = load i8*, i8** %CApath, align 8, !dbg !85
  %18 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %needle.addr, align 8, !dbg !86
  %CApath19 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %18, i32 0, i32 5, !dbg !87
  %19 = load i8*, i8** %CApath19, align 8, !dbg !87
  %call = call i32 @Curl_safe_strcasecompare(i8* %17, i8* %19), !dbg !88
  %tobool20 = icmp ne i32 %call, 0, !dbg !88
  br i1 %tobool20, label %land.lhs.true21, label %if.end, !dbg !89

land.lhs.true21:                                  ; preds = %land.lhs.true18
  %20 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %data.addr, align 8, !dbg !90
  %CAfile = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %20, i32 0, i32 6, !dbg !91
  %21 = load i8*, i8** %CAfile, align 8, !dbg !91
  %22 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %needle.addr, align 8, !dbg !92
  %CAfile22 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %22, i32 0, i32 6, !dbg !93
  %23 = load i8*, i8** %CAfile22, align 8, !dbg !93
  %call23 = call i32 @Curl_safe_strcasecompare(i8* %21, i8* %23), !dbg !94
  %tobool24 = icmp ne i32 %call23, 0, !dbg !94
  br i1 %tobool24, label %land.lhs.true25, label %if.end, !dbg !95

land.lhs.true25:                                  ; preds = %land.lhs.true21
  %24 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %data.addr, align 8, !dbg !96
  %clientcert = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %24, i32 0, i32 7, !dbg !97
  %25 = load i8*, i8** %clientcert, align 8, !dbg !97
  %26 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %needle.addr, align 8, !dbg !98
  %clientcert26 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %26, i32 0, i32 7, !dbg !99
  %27 = load i8*, i8** %clientcert26, align 8, !dbg !99
  %call27 = call i32 @Curl_safe_strcasecompare(i8* %25, i8* %27), !dbg !100
  %tobool28 = icmp ne i32 %call27, 0, !dbg !100
  br i1 %tobool28, label %land.lhs.true29, label %if.end, !dbg !101

land.lhs.true29:                                  ; preds = %land.lhs.true25
  %28 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %data.addr, align 8, !dbg !102
  %cipher_list = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %28, i32 0, i32 10, !dbg !103
  %29 = load i8*, i8** %cipher_list, align 8, !dbg !103
  %30 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %needle.addr, align 8, !dbg !104
  %cipher_list30 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %30, i32 0, i32 10, !dbg !105
  %31 = load i8*, i8** %cipher_list30, align 8, !dbg !105
  %call31 = call i32 @Curl_safe_strcasecompare(i8* %29, i8* %31), !dbg !106
  %tobool32 = icmp ne i32 %call31, 0, !dbg !106
  br i1 %tobool32, label %if.then, label %if.end, !dbg !107

if.then:                                          ; preds = %land.lhs.true29
  store i1 true, i1* %retval, align 1, !dbg !109
  br label %return, !dbg !109

if.end:                                           ; preds = %land.lhs.true29, %land.lhs.true25, %land.lhs.true21, %land.lhs.true18, %land.lhs.true10, %land.lhs.true4, %land.lhs.true, %entry
  store i1 false, i1* %retval, align 1, !dbg !110
  br label %return, !dbg !110

return:                                           ; preds = %if.end, %if.then
  %32 = load i1, i1* %retval, align 1, !dbg !111
  ret i1 %32, !dbg !111
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @Curl_safe_strcasecompare(i8*, i8*) #2

; Function Attrs: nounwind uwtable
define zeroext i1 @Curl_clone_primary_ssl_config(%struct.ssl_primary_config* %source, %struct.ssl_primary_config* %dest) #0 !dbg !45 {
entry:
  %retval = alloca i1, align 1
  %source.addr = alloca %struct.ssl_primary_config*, align 8
  %dest.addr = alloca %struct.ssl_primary_config*, align 8
  store %struct.ssl_primary_config* %source, %struct.ssl_primary_config** %source.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.ssl_primary_config** %source.addr, metadata !112, metadata !55), !dbg !113
  store %struct.ssl_primary_config* %dest, %struct.ssl_primary_config** %dest.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.ssl_primary_config** %dest.addr, metadata !114, metadata !55), !dbg !115
  %0 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %source.addr, align 8, !dbg !116
  %verifyhost = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %0, i32 0, i32 3, !dbg !117
  %1 = load i8, i8* %verifyhost, align 1, !dbg !117
  %tobool = trunc i8 %1 to i1, !dbg !117
  %2 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !118
  %verifyhost1 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %2, i32 0, i32 3, !dbg !119
  %frombool = zext i1 %tobool to i8, !dbg !120
  store i8 %frombool, i8* %verifyhost1, align 1, !dbg !120
  %3 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %source.addr, align 8, !dbg !121
  %verifypeer = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %3, i32 0, i32 2, !dbg !122
  %4 = load i8, i8* %verifypeer, align 8, !dbg !122
  %tobool2 = trunc i8 %4 to i1, !dbg !122
  %5 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !123
  %verifypeer3 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %5, i32 0, i32 2, !dbg !124
  %frombool4 = zext i1 %tobool2 to i8, !dbg !125
  store i8 %frombool4, i8* %verifypeer3, align 8, !dbg !125
  %6 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %source.addr, align 8, !dbg !126
  %version = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %6, i32 0, i32 0, !dbg !127
  %7 = load i64, i64* %version, align 8, !dbg !127
  %8 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !128
  %version5 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %8, i32 0, i32 0, !dbg !129
  store i64 %7, i64* %version5, align 8, !dbg !130
  %9 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %source.addr, align 8, !dbg !131
  %version_max = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %9, i32 0, i32 1, !dbg !132
  %10 = load i64, i64* %version_max, align 8, !dbg !132
  %11 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !133
  %version_max6 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %11, i32 0, i32 1, !dbg !134
  store i64 %10, i64* %version_max6, align 8, !dbg !135
  %12 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %source.addr, align 8, !dbg !136
  %CAfile = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %12, i32 0, i32 6, !dbg !136
  %13 = load i8*, i8** %CAfile, align 8, !dbg !136
  %tobool7 = icmp ne i8* %13, null, !dbg !136
  br i1 %tobool7, label %if.then, label %if.else, !dbg !138

if.then:                                          ; preds = %entry
  %14 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !139
  %15 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %source.addr, align 8, !dbg !139
  %CAfile8 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %15, i32 0, i32 6, !dbg !139
  %16 = load i8*, i8** %CAfile8, align 8, !dbg !139
  %call = call i8* %14(i8* %16), !dbg !139
  %17 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !139
  %CAfile9 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %17, i32 0, i32 6, !dbg !139
  store i8* %call, i8** %CAfile9, align 8, !dbg !139
  %18 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !139
  %CAfile10 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %18, i32 0, i32 6, !dbg !139
  %19 = load i8*, i8** %CAfile10, align 8, !dbg !139
  %tobool11 = icmp ne i8* %19, null, !dbg !139
  br i1 %tobool11, label %if.end, label %if.then12, !dbg !139

if.then12:                                        ; preds = %if.then
  store i1 false, i1* %retval, align 1, !dbg !142
  br label %return, !dbg !142

if.end:                                           ; preds = %if.then
  br label %if.end14, !dbg !145

if.else:                                          ; preds = %entry
  %20 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !147
  %CAfile13 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %20, i32 0, i32 6, !dbg !147
  store i8* null, i8** %CAfile13, align 8, !dbg !147
  br label %if.end14

if.end14:                                         ; preds = %if.else, %if.end
  %21 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %source.addr, align 8, !dbg !149
  %CApath = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %21, i32 0, i32 5, !dbg !149
  %22 = load i8*, i8** %CApath, align 8, !dbg !149
  %tobool15 = icmp ne i8* %22, null, !dbg !149
  br i1 %tobool15, label %if.then16, label %if.else24, !dbg !151

if.then16:                                        ; preds = %if.end14
  %23 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !152
  %24 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %source.addr, align 8, !dbg !152
  %CApath17 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %24, i32 0, i32 5, !dbg !152
  %25 = load i8*, i8** %CApath17, align 8, !dbg !152
  %call18 = call i8* %23(i8* %25), !dbg !152
  %26 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !152
  %CApath19 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %26, i32 0, i32 5, !dbg !152
  store i8* %call18, i8** %CApath19, align 8, !dbg !152
  %27 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !152
  %CApath20 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %27, i32 0, i32 5, !dbg !152
  %28 = load i8*, i8** %CApath20, align 8, !dbg !152
  %tobool21 = icmp ne i8* %28, null, !dbg !152
  br i1 %tobool21, label %if.end23, label %if.then22, !dbg !152

if.then22:                                        ; preds = %if.then16
  store i1 false, i1* %retval, align 1, !dbg !155
  br label %return, !dbg !155

if.end23:                                         ; preds = %if.then16
  br label %if.end26, !dbg !158

if.else24:                                        ; preds = %if.end14
  %29 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !160
  %CApath25 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %29, i32 0, i32 5, !dbg !160
  store i8* null, i8** %CApath25, align 8, !dbg !160
  br label %if.end26

if.end26:                                         ; preds = %if.else24, %if.end23
  %30 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %source.addr, align 8, !dbg !162
  %cipher_list = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %30, i32 0, i32 10, !dbg !162
  %31 = load i8*, i8** %cipher_list, align 8, !dbg !162
  %tobool27 = icmp ne i8* %31, null, !dbg !162
  br i1 %tobool27, label %if.then28, label %if.else36, !dbg !164

if.then28:                                        ; preds = %if.end26
  %32 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !165
  %33 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %source.addr, align 8, !dbg !165
  %cipher_list29 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %33, i32 0, i32 10, !dbg !165
  %34 = load i8*, i8** %cipher_list29, align 8, !dbg !165
  %call30 = call i8* %32(i8* %34), !dbg !165
  %35 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !165
  %cipher_list31 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %35, i32 0, i32 10, !dbg !165
  store i8* %call30, i8** %cipher_list31, align 8, !dbg !165
  %36 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !165
  %cipher_list32 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %36, i32 0, i32 10, !dbg !165
  %37 = load i8*, i8** %cipher_list32, align 8, !dbg !165
  %tobool33 = icmp ne i8* %37, null, !dbg !165
  br i1 %tobool33, label %if.end35, label %if.then34, !dbg !165

if.then34:                                        ; preds = %if.then28
  store i1 false, i1* %retval, align 1, !dbg !168
  br label %return, !dbg !168

if.end35:                                         ; preds = %if.then28
  br label %if.end38, !dbg !171

if.else36:                                        ; preds = %if.end26
  %38 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !173
  %cipher_list37 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %38, i32 0, i32 10, !dbg !173
  store i8* null, i8** %cipher_list37, align 8, !dbg !173
  br label %if.end38

if.end38:                                         ; preds = %if.else36, %if.end35
  %39 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %source.addr, align 8, !dbg !175
  %egdsocket = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %39, i32 0, i32 9, !dbg !175
  %40 = load i8*, i8** %egdsocket, align 8, !dbg !175
  %tobool39 = icmp ne i8* %40, null, !dbg !175
  br i1 %tobool39, label %if.then40, label %if.else48, !dbg !177

if.then40:                                        ; preds = %if.end38
  %41 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !178
  %42 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %source.addr, align 8, !dbg !178
  %egdsocket41 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %42, i32 0, i32 9, !dbg !178
  %43 = load i8*, i8** %egdsocket41, align 8, !dbg !178
  %call42 = call i8* %41(i8* %43), !dbg !178
  %44 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !178
  %egdsocket43 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %44, i32 0, i32 9, !dbg !178
  store i8* %call42, i8** %egdsocket43, align 8, !dbg !178
  %45 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !178
  %egdsocket44 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %45, i32 0, i32 9, !dbg !178
  %46 = load i8*, i8** %egdsocket44, align 8, !dbg !178
  %tobool45 = icmp ne i8* %46, null, !dbg !178
  br i1 %tobool45, label %if.end47, label %if.then46, !dbg !178

if.then46:                                        ; preds = %if.then40
  store i1 false, i1* %retval, align 1, !dbg !181
  br label %return, !dbg !181

if.end47:                                         ; preds = %if.then40
  br label %if.end50, !dbg !184

if.else48:                                        ; preds = %if.end38
  %47 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !186
  %egdsocket49 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %47, i32 0, i32 9, !dbg !186
  store i8* null, i8** %egdsocket49, align 8, !dbg !186
  br label %if.end50

if.end50:                                         ; preds = %if.else48, %if.end47
  %48 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %source.addr, align 8, !dbg !188
  %random_file = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %48, i32 0, i32 8, !dbg !188
  %49 = load i8*, i8** %random_file, align 8, !dbg !188
  %tobool51 = icmp ne i8* %49, null, !dbg !188
  br i1 %tobool51, label %if.then52, label %if.else60, !dbg !190

if.then52:                                        ; preds = %if.end50
  %50 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !191
  %51 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %source.addr, align 8, !dbg !191
  %random_file53 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %51, i32 0, i32 8, !dbg !191
  %52 = load i8*, i8** %random_file53, align 8, !dbg !191
  %call54 = call i8* %50(i8* %52), !dbg !191
  %53 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !191
  %random_file55 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %53, i32 0, i32 8, !dbg !191
  store i8* %call54, i8** %random_file55, align 8, !dbg !191
  %54 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !191
  %random_file56 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %54, i32 0, i32 8, !dbg !191
  %55 = load i8*, i8** %random_file56, align 8, !dbg !191
  %tobool57 = icmp ne i8* %55, null, !dbg !191
  br i1 %tobool57, label %if.end59, label %if.then58, !dbg !191

if.then58:                                        ; preds = %if.then52
  store i1 false, i1* %retval, align 1, !dbg !194
  br label %return, !dbg !194

if.end59:                                         ; preds = %if.then52
  br label %if.end62, !dbg !197

if.else60:                                        ; preds = %if.end50
  %56 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !199
  %random_file61 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %56, i32 0, i32 8, !dbg !199
  store i8* null, i8** %random_file61, align 8, !dbg !199
  br label %if.end62

if.end62:                                         ; preds = %if.else60, %if.end59
  %57 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %source.addr, align 8, !dbg !201
  %clientcert = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %57, i32 0, i32 7, !dbg !201
  %58 = load i8*, i8** %clientcert, align 8, !dbg !201
  %tobool63 = icmp ne i8* %58, null, !dbg !201
  br i1 %tobool63, label %if.then64, label %if.else72, !dbg !203

if.then64:                                        ; preds = %if.end62
  %59 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !204
  %60 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %source.addr, align 8, !dbg !204
  %clientcert65 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %60, i32 0, i32 7, !dbg !204
  %61 = load i8*, i8** %clientcert65, align 8, !dbg !204
  %call66 = call i8* %59(i8* %61), !dbg !204
  %62 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !204
  %clientcert67 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %62, i32 0, i32 7, !dbg !204
  store i8* %call66, i8** %clientcert67, align 8, !dbg !204
  %63 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !204
  %clientcert68 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %63, i32 0, i32 7, !dbg !204
  %64 = load i8*, i8** %clientcert68, align 8, !dbg !204
  %tobool69 = icmp ne i8* %64, null, !dbg !204
  br i1 %tobool69, label %if.end71, label %if.then70, !dbg !204

if.then70:                                        ; preds = %if.then64
  store i1 false, i1* %retval, align 1, !dbg !207
  br label %return, !dbg !207

if.end71:                                         ; preds = %if.then64
  br label %if.end74, !dbg !210

if.else72:                                        ; preds = %if.end62
  %65 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !212
  %clientcert73 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %65, i32 0, i32 7, !dbg !212
  store i8* null, i8** %clientcert73, align 8, !dbg !212
  br label %if.end74

if.end74:                                         ; preds = %if.else72, %if.end71
  %66 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !214
  %clientcert75 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %66, i32 0, i32 7, !dbg !215
  %67 = load i8*, i8** %clientcert75, align 8, !dbg !215
  %tobool76 = icmp ne i8* %67, null, !dbg !214
  br i1 %tobool76, label %cond.true, label %cond.false, !dbg !214

cond.true:                                        ; preds = %if.end74
  br label %cond.end, !dbg !216

cond.false:                                       ; preds = %if.end74
  %68 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %source.addr, align 8, !dbg !218
  %sessionid = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %68, i32 0, i32 11, !dbg !220
  %69 = load i8, i8* %sessionid, align 8, !dbg !220
  %tobool77 = trunc i8 %69 to i1, !dbg !220
  %conv = zext i1 %tobool77 to i32, !dbg !218
  br label %cond.end, !dbg !221

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ 0, %cond.true ], [ %conv, %cond.false ], !dbg !222
  %tobool78 = icmp ne i32 %cond, 0, !dbg !224
  %70 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %dest.addr, align 8, !dbg !225
  %sessionid79 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %70, i32 0, i32 11, !dbg !226
  %frombool80 = zext i1 %tobool78 to i8, !dbg !227
  store i8 %frombool80, i8* %sessionid79, align 8, !dbg !227
  store i1 true, i1* %retval, align 1, !dbg !228
  br label %return, !dbg !228

return:                                           ; preds = %cond.end, %if.then70, %if.then58, %if.then46, %if.then34, %if.then22, %if.then12
  %71 = load i1, i1* %retval, align 1, !dbg !229
  ret i1 %71, !dbg !229
}

; Function Attrs: nounwind uwtable
define void @Curl_free_primary_ssl_config(%struct.ssl_primary_config* %sslc) #0 !dbg !46 {
entry:
  %sslc.addr = alloca %struct.ssl_primary_config*, align 8
  store %struct.ssl_primary_config* %sslc, %struct.ssl_primary_config** %sslc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.ssl_primary_config** %sslc.addr, metadata !230, metadata !55), !dbg !231
  br label %do.body, !dbg !232

do.body:                                          ; preds = %entry
  %0 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !233
  %1 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %sslc.addr, align 8, !dbg !233
  %CAfile = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %1, i32 0, i32 6, !dbg !233
  %2 = load i8*, i8** %CAfile, align 8, !dbg !233
  call void %0(i8* %2), !dbg !233
  %3 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %sslc.addr, align 8, !dbg !233
  %CAfile1 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %3, i32 0, i32 6, !dbg !233
  store i8* null, i8** %CAfile1, align 8, !dbg !233
  br label %do.end, !dbg !233

do.end:                                           ; preds = %do.body
  br label %do.body2, !dbg !236

do.body2:                                         ; preds = %do.end
  %4 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !237
  %5 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %sslc.addr, align 8, !dbg !237
  %CApath = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %5, i32 0, i32 5, !dbg !237
  %6 = load i8*, i8** %CApath, align 8, !dbg !237
  call void %4(i8* %6), !dbg !237
  %7 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %sslc.addr, align 8, !dbg !237
  %CApath3 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %7, i32 0, i32 5, !dbg !237
  store i8* null, i8** %CApath3, align 8, !dbg !237
  br label %do.end4, !dbg !237

do.end4:                                          ; preds = %do.body2
  br label %do.body5, !dbg !240

do.body5:                                         ; preds = %do.end4
  %8 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !241
  %9 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %sslc.addr, align 8, !dbg !241
  %cipher_list = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %9, i32 0, i32 10, !dbg !241
  %10 = load i8*, i8** %cipher_list, align 8, !dbg !241
  call void %8(i8* %10), !dbg !241
  %11 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %sslc.addr, align 8, !dbg !241
  %cipher_list6 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %11, i32 0, i32 10, !dbg !241
  store i8* null, i8** %cipher_list6, align 8, !dbg !241
  br label %do.end7, !dbg !241

do.end7:                                          ; preds = %do.body5
  br label %do.body8, !dbg !244

do.body8:                                         ; preds = %do.end7
  %12 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !245
  %13 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %sslc.addr, align 8, !dbg !245
  %egdsocket = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %13, i32 0, i32 9, !dbg !245
  %14 = load i8*, i8** %egdsocket, align 8, !dbg !245
  call void %12(i8* %14), !dbg !245
  %15 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %sslc.addr, align 8, !dbg !245
  %egdsocket9 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %15, i32 0, i32 9, !dbg !245
  store i8* null, i8** %egdsocket9, align 8, !dbg !245
  br label %do.end10, !dbg !245

do.end10:                                         ; preds = %do.body8
  br label %do.body11, !dbg !248

do.body11:                                        ; preds = %do.end10
  %16 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !249
  %17 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %sslc.addr, align 8, !dbg !249
  %random_file = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %17, i32 0, i32 8, !dbg !249
  %18 = load i8*, i8** %random_file, align 8, !dbg !249
  call void %16(i8* %18), !dbg !249
  %19 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %sslc.addr, align 8, !dbg !249
  %random_file12 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %19, i32 0, i32 8, !dbg !249
  store i8* null, i8** %random_file12, align 8, !dbg !249
  br label %do.end13, !dbg !249

do.end13:                                         ; preds = %do.body11
  br label %do.body14, !dbg !252

do.body14:                                        ; preds = %do.end13
  %20 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !253
  %21 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %sslc.addr, align 8, !dbg !253
  %clientcert = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %21, i32 0, i32 7, !dbg !253
  %22 = load i8*, i8** %clientcert, align 8, !dbg !253
  call void %20(i8* %22), !dbg !253
  %23 = load %struct.ssl_primary_config*, %struct.ssl_primary_config** %sslc.addr, align 8, !dbg !253
  %clientcert15 = getelementptr inbounds %struct.ssl_primary_config, %struct.ssl_primary_config* %23, i32 0, i32 7, !dbg !253
  store i8* null, i8** %clientcert15, align 8, !dbg !253
  br label %do.end16, !dbg !253

do.end16:                                         ; preds = %do.body14
  ret void, !dbg !256
}

; Function Attrs: nounwind uwtable
define i32 @Curl_ssl_backend() #0 !dbg !49 {
entry:
  ret i32 0, !dbg !257
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!51, !52}
!llvm.ident = !{!53}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !18, subprograms: !20)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/vtls/vtls.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 2222, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17}
!6 = !DIEnumerator(name: "CURLSSLBACKEND_NONE", value: 0)
!7 = !DIEnumerator(name: "CURLSSLBACKEND_OPENSSL", value: 1)
!8 = !DIEnumerator(name: "CURLSSLBACKEND_GNUTLS", value: 2)
!9 = !DIEnumerator(name: "CURLSSLBACKEND_NSS", value: 3)
!10 = !DIEnumerator(name: "CURLSSLBACKEND_OBSOLETE4", value: 4)
!11 = !DIEnumerator(name: "CURLSSLBACKEND_GSKIT", value: 5)
!12 = !DIEnumerator(name: "CURLSSLBACKEND_POLARSSL", value: 6)
!13 = !DIEnumerator(name: "CURLSSLBACKEND_CYASSL", value: 7)
!14 = !DIEnumerator(name: "CURLSSLBACKEND_SCHANNEL", value: 8)
!15 = !DIEnumerator(name: "CURLSSLBACKEND_DARWINSSL", value: 9)
!16 = !DIEnumerator(name: "CURLSSLBACKEND_AXTLS", value: 10)
!17 = !DIEnumerator(name: "CURLSSLBACKEND_MBEDTLS", value: 11)
!18 = !{!19}
!19 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!20 = !{!21, !45, !46, !49}
!21 = distinct !DISubprogram(name: "Curl_ssl_config_matches", scope: !1, file: !1, line: 94, type: !22, isLocal: false, isDefinition: true, scopeLine: 96, flags: DIFlagPrototyped, isOptimized: false, variables: !44)
!22 = !DISubroutineType(types: !23)
!23 = !{!24, !25, !25}
!24 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!25 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !26, size: 64, align: 64)
!26 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_primary_config", file: !27, line: 351, size: 640, align: 64, elements: !28)
!27 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/urldata.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!28 = !{!29, !31, !32, !33, !34, !35, !38, !39, !40, !41, !42, !43}
!29 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !26, file: !27, line: 352, baseType: !30, size: 64, align: 64)
!30 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!31 = !DIDerivedType(tag: DW_TAG_member, name: "version_max", scope: !26, file: !27, line: 353, baseType: !30, size: 64, align: 64, offset: 64)
!32 = !DIDerivedType(tag: DW_TAG_member, name: "verifypeer", scope: !26, file: !27, line: 354, baseType: !24, size: 8, align: 8, offset: 128)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "verifyhost", scope: !26, file: !27, line: 355, baseType: !24, size: 8, align: 8, offset: 136)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "verifystatus", scope: !26, file: !27, line: 356, baseType: !24, size: 8, align: 8, offset: 144)
!35 = !DIDerivedType(tag: DW_TAG_member, name: "CApath", scope: !26, file: !27, line: 357, baseType: !36, size: 64, align: 64, offset: 192)
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !37, size: 64, align: 64)
!37 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "CAfile", scope: !26, file: !27, line: 358, baseType: !36, size: 64, align: 64, offset: 256)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "clientcert", scope: !26, file: !27, line: 359, baseType: !36, size: 64, align: 64, offset: 320)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "random_file", scope: !26, file: !27, line: 360, baseType: !36, size: 64, align: 64, offset: 384)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "egdsocket", scope: !26, file: !27, line: 361, baseType: !36, size: 64, align: 64, offset: 448)
!42 = !DIDerivedType(tag: DW_TAG_member, name: "cipher_list", scope: !26, file: !27, line: 362, baseType: !36, size: 64, align: 64, offset: 512)
!43 = !DIDerivedType(tag: DW_TAG_member, name: "sessionid", scope: !26, file: !27, line: 363, baseType: !24, size: 8, align: 8, offset: 576)
!44 = !{}
!45 = distinct !DISubprogram(name: "Curl_clone_primary_ssl_config", scope: !1, file: !1, line: 111, type: !22, isLocal: false, isDefinition: true, scopeLine: 113, flags: DIFlagPrototyped, isOptimized: false, variables: !44)
!46 = distinct !DISubprogram(name: "Curl_free_primary_ssl_config", scope: !1, file: !1, line: 131, type: !47, isLocal: false, isDefinition: true, scopeLine: 132, flags: DIFlagPrototyped, isOptimized: false, variables: !44)
!47 = !DISubroutineType(types: !48)
!48 = !{null, !25}
!49 = distinct !DISubprogram(name: "Curl_ssl_backend", scope: !1, file: !1, line: 141, type: !50, isLocal: false, isDefinition: true, scopeLine: 142, flags: DIFlagPrototyped, isOptimized: false, variables: !44)
!50 = !DISubroutineType(types: !18)
!51 = !{i32 2, !"Dwarf Version", i32 4}
!52 = !{i32 2, !"Debug Info Version", i32 3}
!53 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!54 = !DILocalVariable(name: "data", arg: 1, scope: !21, file: !1, line: 94, type: !25)
!55 = !DIExpression()
!56 = !DILocation(line: 94, column: 52, scope: !21)
!57 = !DILocalVariable(name: "needle", arg: 2, scope: !21, file: !1, line: 95, type: !25)
!58 = !DILocation(line: 95, column: 52, scope: !21)
!59 = !DILocation(line: 97, column: 7, scope: !60)
!60 = distinct !DILexicalBlock(scope: !21, file: !1, line: 97, column: 6)
!61 = !DILocation(line: 97, column: 13, scope: !60)
!62 = !DILocation(line: 97, column: 24, scope: !60)
!63 = !DILocation(line: 97, column: 32, scope: !60)
!64 = !DILocation(line: 97, column: 21, scope: !60)
!65 = !DILocation(line: 97, column: 41, scope: !60)
!66 = !DILocation(line: 98, column: 7, scope: !60)
!67 = !DILocation(line: 98, column: 13, scope: !60)
!68 = !DILocation(line: 98, column: 28, scope: !60)
!69 = !DILocation(line: 98, column: 36, scope: !60)
!70 = !DILocation(line: 98, column: 25, scope: !60)
!71 = !DILocation(line: 98, column: 49, scope: !60)
!72 = !DILocation(line: 99, column: 7, scope: !60)
!73 = !DILocation(line: 99, column: 13, scope: !60)
!74 = !DILocation(line: 99, column: 27, scope: !60)
!75 = !DILocation(line: 99, column: 35, scope: !60)
!76 = !DILocation(line: 99, column: 24, scope: !60)
!77 = !DILocation(line: 99, column: 47, scope: !60)
!78 = !DILocation(line: 100, column: 7, scope: !60)
!79 = !DILocation(line: 100, column: 13, scope: !60)
!80 = !DILocation(line: 100, column: 27, scope: !60)
!81 = !DILocation(line: 100, column: 35, scope: !60)
!82 = !DILocation(line: 100, column: 24, scope: !60)
!83 = !DILocation(line: 100, column: 47, scope: !60)
!84 = !DILocation(line: 101, column: 31, scope: !60)
!85 = !DILocation(line: 101, column: 37, scope: !60)
!86 = !DILocation(line: 101, column: 45, scope: !60)
!87 = !DILocation(line: 101, column: 53, scope: !60)
!88 = !DILocation(line: 101, column: 6, scope: !60)
!89 = !DILocation(line: 101, column: 61, scope: !60)
!90 = !DILocation(line: 102, column: 31, scope: !60)
!91 = !DILocation(line: 102, column: 37, scope: !60)
!92 = !DILocation(line: 102, column: 45, scope: !60)
!93 = !DILocation(line: 102, column: 53, scope: !60)
!94 = !DILocation(line: 102, column: 6, scope: !60)
!95 = !DILocation(line: 102, column: 61, scope: !60)
!96 = !DILocation(line: 103, column: 31, scope: !60)
!97 = !DILocation(line: 103, column: 37, scope: !60)
!98 = !DILocation(line: 103, column: 49, scope: !60)
!99 = !DILocation(line: 103, column: 57, scope: !60)
!100 = !DILocation(line: 103, column: 6, scope: !60)
!101 = !DILocation(line: 103, column: 69, scope: !60)
!102 = !DILocation(line: 104, column: 31, scope: !60)
!103 = !DILocation(line: 104, column: 37, scope: !60)
!104 = !DILocation(line: 104, column: 50, scope: !60)
!105 = !DILocation(line: 104, column: 58, scope: !60)
!106 = !DILocation(line: 104, column: 6, scope: !60)
!107 = !DILocation(line: 97, column: 6, scope: !108)
!108 = !DILexicalBlockFile(scope: !21, file: !1, discriminator: 1)
!109 = !DILocation(line: 105, column: 5, scope: !60)
!110 = !DILocation(line: 107, column: 3, scope: !21)
!111 = !DILocation(line: 108, column: 1, scope: !21)
!112 = !DILocalVariable(name: "source", arg: 1, scope: !45, file: !1, line: 111, type: !25)
!113 = !DILocation(line: 111, column: 58, scope: !45)
!114 = !DILocalVariable(name: "dest", arg: 2, scope: !45, file: !1, line: 112, type: !25)
!115 = !DILocation(line: 112, column: 58, scope: !45)
!116 = !DILocation(line: 114, column: 22, scope: !45)
!117 = !DILocation(line: 114, column: 30, scope: !45)
!118 = !DILocation(line: 114, column: 3, scope: !45)
!119 = !DILocation(line: 114, column: 9, scope: !45)
!120 = !DILocation(line: 114, column: 20, scope: !45)
!121 = !DILocation(line: 115, column: 22, scope: !45)
!122 = !DILocation(line: 115, column: 30, scope: !45)
!123 = !DILocation(line: 115, column: 3, scope: !45)
!124 = !DILocation(line: 115, column: 9, scope: !45)
!125 = !DILocation(line: 115, column: 20, scope: !45)
!126 = !DILocation(line: 116, column: 19, scope: !45)
!127 = !DILocation(line: 116, column: 27, scope: !45)
!128 = !DILocation(line: 116, column: 3, scope: !45)
!129 = !DILocation(line: 116, column: 9, scope: !45)
!130 = !DILocation(line: 116, column: 17, scope: !45)
!131 = !DILocation(line: 117, column: 23, scope: !45)
!132 = !DILocation(line: 117, column: 31, scope: !45)
!133 = !DILocation(line: 117, column: 3, scope: !45)
!134 = !DILocation(line: 117, column: 9, scope: !45)
!135 = !DILocation(line: 117, column: 21, scope: !45)
!136 = !DILocation(line: 119, column: 3, scope: !137)
!137 = distinct !DILexicalBlock(scope: !45, file: !1, line: 119, column: 3)
!138 = !DILocation(line: 119, column: 3, scope: !45)
!139 = !DILocation(line: 119, column: 3, scope: !140)
!140 = !DILexicalBlockFile(scope: !141, file: !1, discriminator: 1)
!141 = distinct !DILexicalBlock(scope: !137, file: !1, line: 119, column: 3)
!142 = !DILocation(line: 119, column: 3, scope: !143)
!143 = !DILexicalBlockFile(scope: !144, file: !1, discriminator: 2)
!144 = distinct !DILexicalBlock(scope: !141, file: !1, line: 119, column: 3)
!145 = !DILocation(line: 119, column: 3, scope: !146)
!146 = !DILexicalBlockFile(scope: !141, file: !1, discriminator: 3)
!147 = !DILocation(line: 119, column: 3, scope: !148)
!148 = !DILexicalBlockFile(scope: !137, file: !1, discriminator: 4)
!149 = !DILocation(line: 120, column: 3, scope: !150)
!150 = distinct !DILexicalBlock(scope: !45, file: !1, line: 120, column: 3)
!151 = !DILocation(line: 120, column: 3, scope: !45)
!152 = !DILocation(line: 120, column: 3, scope: !153)
!153 = !DILexicalBlockFile(scope: !154, file: !1, discriminator: 1)
!154 = distinct !DILexicalBlock(scope: !150, file: !1, line: 120, column: 3)
!155 = !DILocation(line: 120, column: 3, scope: !156)
!156 = !DILexicalBlockFile(scope: !157, file: !1, discriminator: 2)
!157 = distinct !DILexicalBlock(scope: !154, file: !1, line: 120, column: 3)
!158 = !DILocation(line: 120, column: 3, scope: !159)
!159 = !DILexicalBlockFile(scope: !154, file: !1, discriminator: 3)
!160 = !DILocation(line: 120, column: 3, scope: !161)
!161 = !DILexicalBlockFile(scope: !150, file: !1, discriminator: 4)
!162 = !DILocation(line: 121, column: 3, scope: !163)
!163 = distinct !DILexicalBlock(scope: !45, file: !1, line: 121, column: 3)
!164 = !DILocation(line: 121, column: 3, scope: !45)
!165 = !DILocation(line: 121, column: 3, scope: !166)
!166 = !DILexicalBlockFile(scope: !167, file: !1, discriminator: 1)
!167 = distinct !DILexicalBlock(scope: !163, file: !1, line: 121, column: 3)
!168 = !DILocation(line: 121, column: 3, scope: !169)
!169 = !DILexicalBlockFile(scope: !170, file: !1, discriminator: 2)
!170 = distinct !DILexicalBlock(scope: !167, file: !1, line: 121, column: 3)
!171 = !DILocation(line: 121, column: 3, scope: !172)
!172 = !DILexicalBlockFile(scope: !167, file: !1, discriminator: 3)
!173 = !DILocation(line: 121, column: 3, scope: !174)
!174 = !DILexicalBlockFile(scope: !163, file: !1, discriminator: 4)
!175 = !DILocation(line: 122, column: 3, scope: !176)
!176 = distinct !DILexicalBlock(scope: !45, file: !1, line: 122, column: 3)
!177 = !DILocation(line: 122, column: 3, scope: !45)
!178 = !DILocation(line: 122, column: 3, scope: !179)
!179 = !DILexicalBlockFile(scope: !180, file: !1, discriminator: 1)
!180 = distinct !DILexicalBlock(scope: !176, file: !1, line: 122, column: 3)
!181 = !DILocation(line: 122, column: 3, scope: !182)
!182 = !DILexicalBlockFile(scope: !183, file: !1, discriminator: 2)
!183 = distinct !DILexicalBlock(scope: !180, file: !1, line: 122, column: 3)
!184 = !DILocation(line: 122, column: 3, scope: !185)
!185 = !DILexicalBlockFile(scope: !180, file: !1, discriminator: 3)
!186 = !DILocation(line: 122, column: 3, scope: !187)
!187 = !DILexicalBlockFile(scope: !176, file: !1, discriminator: 4)
!188 = !DILocation(line: 123, column: 3, scope: !189)
!189 = distinct !DILexicalBlock(scope: !45, file: !1, line: 123, column: 3)
!190 = !DILocation(line: 123, column: 3, scope: !45)
!191 = !DILocation(line: 123, column: 3, scope: !192)
!192 = !DILexicalBlockFile(scope: !193, file: !1, discriminator: 1)
!193 = distinct !DILexicalBlock(scope: !189, file: !1, line: 123, column: 3)
!194 = !DILocation(line: 123, column: 3, scope: !195)
!195 = !DILexicalBlockFile(scope: !196, file: !1, discriminator: 2)
!196 = distinct !DILexicalBlock(scope: !193, file: !1, line: 123, column: 3)
!197 = !DILocation(line: 123, column: 3, scope: !198)
!198 = !DILexicalBlockFile(scope: !193, file: !1, discriminator: 3)
!199 = !DILocation(line: 123, column: 3, scope: !200)
!200 = !DILexicalBlockFile(scope: !189, file: !1, discriminator: 4)
!201 = !DILocation(line: 124, column: 3, scope: !202)
!202 = distinct !DILexicalBlock(scope: !45, file: !1, line: 124, column: 3)
!203 = !DILocation(line: 124, column: 3, scope: !45)
!204 = !DILocation(line: 124, column: 3, scope: !205)
!205 = !DILexicalBlockFile(scope: !206, file: !1, discriminator: 1)
!206 = distinct !DILexicalBlock(scope: !202, file: !1, line: 124, column: 3)
!207 = !DILocation(line: 124, column: 3, scope: !208)
!208 = !DILexicalBlockFile(scope: !209, file: !1, discriminator: 2)
!209 = distinct !DILexicalBlock(scope: !206, file: !1, line: 124, column: 3)
!210 = !DILocation(line: 124, column: 3, scope: !211)
!211 = !DILexicalBlockFile(scope: !206, file: !1, discriminator: 3)
!212 = !DILocation(line: 124, column: 3, scope: !213)
!213 = !DILexicalBlockFile(scope: !202, file: !1, discriminator: 4)
!214 = !DILocation(line: 127, column: 22, scope: !45)
!215 = !DILocation(line: 127, column: 28, scope: !45)
!216 = !DILocation(line: 127, column: 22, scope: !217)
!217 = !DILexicalBlockFile(scope: !45, file: !1, discriminator: 1)
!218 = !DILocation(line: 127, column: 49, scope: !219)
!219 = !DILexicalBlockFile(scope: !45, file: !1, discriminator: 2)
!220 = !DILocation(line: 127, column: 57, scope: !219)
!221 = !DILocation(line: 127, column: 22, scope: !219)
!222 = !DILocation(line: 127, column: 22, scope: !223)
!223 = !DILexicalBlockFile(scope: !45, file: !1, discriminator: 3)
!224 = !DILocation(line: 127, column: 21, scope: !223)
!225 = !DILocation(line: 127, column: 3, scope: !223)
!226 = !DILocation(line: 127, column: 9, scope: !223)
!227 = !DILocation(line: 127, column: 19, scope: !223)
!228 = !DILocation(line: 128, column: 3, scope: !45)
!229 = !DILocation(line: 129, column: 1, scope: !45)
!230 = !DILocalVariable(name: "sslc", arg: 1, scope: !46, file: !1, line: 131, type: !25)
!231 = !DILocation(line: 131, column: 62, scope: !46)
!232 = !DILocation(line: 133, column: 3, scope: !46)
!233 = !DILocation(line: 133, column: 3, scope: !234)
!234 = !DILexicalBlockFile(scope: !235, file: !1, discriminator: 1)
!235 = distinct !DILexicalBlock(scope: !46, file: !1, line: 133, column: 3)
!236 = !DILocation(line: 134, column: 3, scope: !46)
!237 = !DILocation(line: 134, column: 3, scope: !238)
!238 = !DILexicalBlockFile(scope: !239, file: !1, discriminator: 1)
!239 = distinct !DILexicalBlock(scope: !46, file: !1, line: 134, column: 3)
!240 = !DILocation(line: 135, column: 3, scope: !46)
!241 = !DILocation(line: 135, column: 3, scope: !242)
!242 = !DILexicalBlockFile(scope: !243, file: !1, discriminator: 1)
!243 = distinct !DILexicalBlock(scope: !46, file: !1, line: 135, column: 3)
!244 = !DILocation(line: 136, column: 3, scope: !46)
!245 = !DILocation(line: 136, column: 3, scope: !246)
!246 = !DILexicalBlockFile(scope: !247, file: !1, discriminator: 1)
!247 = distinct !DILexicalBlock(scope: !46, file: !1, line: 136, column: 3)
!248 = !DILocation(line: 137, column: 3, scope: !46)
!249 = !DILocation(line: 137, column: 3, scope: !250)
!250 = !DILexicalBlockFile(scope: !251, file: !1, discriminator: 1)
!251 = distinct !DILexicalBlock(scope: !46, file: !1, line: 137, column: 3)
!252 = !DILocation(line: 138, column: 3, scope: !46)
!253 = !DILocation(line: 138, column: 3, scope: !254)
!254 = !DILexicalBlockFile(scope: !255, file: !1, discriminator: 1)
!255 = distinct !DILexicalBlock(scope: !46, file: !1, line: 138, column: 3)
!256 = !DILocation(line: 139, column: 1, scope: !46)
!257 = !DILocation(line: 143, column: 3, scope: !49)
